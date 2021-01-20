//******************************************************************************
//  Created:    2018/1/3   11:42
//  File base:  tester
//  Copyright:  iTest
//  Version:
//
//  Purpose:    This header file defines the types and definitions used to
//              interface to the WT tester.
//******************************************************************************

#ifndef __NbiotTester_h__
#define __NbiotTester_h__

#include "testerCommon.h"

#ifndef _Export
#define _Export __declspec(dllexport)
#define _Import __declspec(dllimport)
#endif

#ifdef NbiotTester_DLL_EXPORTS
#if defined(__cplusplus) || defined(c_plusplus) || defined(_cplusplus)
#define FlowTester_DLL_API extern "C" __declspec(dllexport)
#else
#define FlowTester_DLL_API extern __declspec(dllexport)
#endif
#else
#if defined(__cplusplus) || defined(c_plusplus) || defined(_cplusplus)
#define FlowTester_DLL_API extern "C" __declspec(dllimport)
#else
#define FlowTester_DLL_API __declspec(dllimport)
#endif
#endif

typedef struct
{
	double interval_from_last_operate;        //与上个VSA操作的间隔. ms
	double sample_freq;                  //采样速率，Hz；108、208C支持15M,30M,60M,120M,其余只支持120M
	double attenuation;                  //外部衰减，dB
	double freq;               //VSA载波频率,单位：Hz
	double max_power;          //输入的最大功率,dBm; (最好在实际输出到仪器的功率基础上再加12dB，如果接收功率范围未知，建议事先Auto Range)
	double smp_time;           //采样时间,us
	int rfPort;             //指定VSA使用的RF端口

	int trig_type;          //触发模式,WT_TRIG_TYPE_ENUM
	double trig_level;         //触发电平,与max_power的差距,dB
	double trig_timeout;       //触发等待超时,sec（该时间与TimeoutWaiting的时间相互独立）
	double trig_pretime;       //触发保留时间,保留触发前若干时间内的数据,us
	int reserveds[50];
}VsaControl;

typedef struct
{
	double interval_from_last_operate;        //与上个VSG操作的间隔. ms
	double sample_freq;                  //采样速率，Hz；108、208C支持15M,30M,60M,120M,其余只支持120M
	double attenuation;                  //外部衰减，dB
	double freq;               //VSG载波频率,单位：Hz
	double power;              //VSG功率,dBm
	int rfPort;             //指定VSG使用的RF端口
	int repeat;             //循环发送次数
	double wave_gap;           //两次发送间隔，us
	int wave_index;             //第几个信号，从0开始
	int waveType;           //Wave类型，WT_SIGNAL_ENUM. SIG_USERFILE: 读取本地wave文件; SIG_TESTERFILE: 使用仪器存储的wave文件(WT-208固件版本低于或等于3.0.1.10的不支持该项); (其余选项（除SIG_USERFILE和SIG_TESTERFILE以外的选项）：仅WT-208仪器支持)
	int reserveds[18];
}VsgControl;

#define MAX_VSG_WAVE_COUNT 10
typedef struct
{
	int waves_count;
	char *waves[MAX_VSG_WAVE_COUNT];
}VsgWaves;

enum ALG_TYPE
{
	Npusch,
	Nprach,
};

typedef struct
{
	int npusch_format; /*NPUSCH信道格式，enum NB_IOT_NPUSCH_FORMAT*/
	int resource_unit_subcarr_num; //一个资源单元调用的子载波数(N_RA_SC)（1，3，6，12）
	unsigned int qm; /*调制映射指数（
					 resource_unit_subcarr_num=1：BPSK或者QPSK，
					 resource_unit_subcarr_num>1：QPSK，
					 enum NB_IOT_NPUSCH_QM */
	int deta_f;      /*子载波间隔（支持3.75kHz和15kHz两种子载波间隔）enum NB_IOT_SUBCARRIER_DETA_FREQ*/
	unsigned int mcs; /*调制编码指数（deta_f(3.75kHz): 0~10，deta_f(15kHZ): 0~13）*/
	int ru_sub_carr_pos; /*RU子载波映射的偏移量（
						 deta_f=3.75kHz并且resource_unit_subcarr_num=1，取值0~47。
						 deta_f=15kHz，resource_unit_subcarr_num=1，取值0~11
									  resource_unit_subcarr_num=3，取值0，3，6，9，
									  resource_unit_subcarr_num=6，取值0，6，
									  resource_unit_subcarr_num=12，取值0）*/
	int cell_id;    /*NB-IOT小区号 0~503*/
	int alpha_shift;  /*resource_unit_subcarr_num>1时的循环移位（
					  resource_unit_subcarr_num=1无效，
					  resource_unit_subcarr_num=3：0,1,2,
					  resource_unit_subcarr_num=6: 0,1,2,3,
					  resource_unit_subcarr_num=12: 0）*/
	int dmrs_group_hopping_flag; /*DMRS组跳标志位（0-不使能，1-使能）*/
	int time_input_flag;     /*控制以下两个字段是否允许用户输入（0-不使能，1-使能）*/
	int npusch_rep_time;    /*NPUSCH信道重复次数(1,2,4,8,16,32,64,128)*/
	int npusch_total_ru;    /*NPUSCH总共调度的RU数目(1,2,3,4,5,6,8,10)*/
	int reserveds[20];
}NpuschParameters;

typedef struct
{
	int preamble_format;  /*随机接入信道的格式 enum NB_IOT_NPRACH_FORMAT*/
	int used_subcarr_num;  /*使用的子载波个数(N_RA_SC)（12，24，36，48）*/
	int sub_carr_pos;     /*子载波偏移(SC_offset)(0,12,24,36,2,18,34)*/
	int init_sc_idx;     /*子载波初始化索引(InitSCIdx)（0~used_subcarr_num-1)*/
	int nprach_rep_time;    /*NPRACH信道重复次数(1,2,4,8,16,32,64,128)*/
	int npusch_deta_f;      /*NPUSCH信道的子载波间隔（支持3.75kHz和15kHz两种子载波间隔）enum NB_IOT_SUBCARRIER_DETA_FREQ*/
	int cell_id;    /*NB-IOT小区号 0~503*/
	int reserveds[19];
}NprachParameters;

typedef struct
{
	int demod;              //802.11 分析模式.WT_DEMOD_ENUM
	enum ALG_TYPE alg_type;
	union
	{
		NpuschParameters npusch_params;
		NprachParameters nprach_params;
	};
}AlgParameters;

#define MAX_FLOW_COUNT 512
#define MAX_BAND_COUNT 100

typedef struct
{
	VsgWaves vsg_waves; /* vsa、vsg操作流中所有vsg操作需要用到的信号 */
	int reserved;
	int vsg_control_before_master_start_valid; /*0: vsg_control_before_master_start无效，1：vsg_control_before_master_start有效*/
	VsgControl vsg_control_before_master_start; /*在主 vsa启动前的VSG操作*/
	VsaControl vsa_master_control; /*主VSA操作*/
	int vsg_control_flow_after_master_count; /*主vsa操作后的vsg操作个数*/
	int vsa_control_flow_after_master_count; /*主vsa操作后的vsa操作个数*/
	VsgControl vsg_control_flow_after_master[MAX_FLOW_COUNT]; /*主vsa操作后的vsg操作流，
															  每个vsg操作间隔都是相对前一个vsg操作来的，
															  第一个vsg操作的间隔是相对主vsa操作的*/
	VsaControl vsa_control_flow_after_master[MAX_FLOW_COUNT]; /*主vsa操作后的vsa操作流，
															  每个vsa操作间隔都是相对前一个vsa操作来的,
															  第一个vsa操作的间隔是相对主vsa操作的*/
	int band_count; /*band 的个数*/
	int each_band_vsg_count[MAX_BAND_COUNT]; /*每个band的vsg流数个数,第一个band的vsg流数个数不包含vsg_control_before_master_start*/
	int each_band_vsa_count[MAX_BAND_COUNT]; /*每个band的vsa流数个数,第一个band的vsa流数个数包含vsa_master_control*/
}VsaVsgControlFlow;

//*****************************************************************************
//                           VSA VSG Status
//*****************************************************************************
enum WT_VSA_VSG_FLOW_STATE
{
	WT_FLOW_STATE_DONE,
	WT_FLOW_STATE_RUNNING,
	WT_FLOW_STATE_TIMEOUT,
	WT_FLOW_STATE_ERR_DONE,
	WT_FLOW_STATE_WAITING
};

//************************************
// Method:    WT_SetVsaVsgControlFlow
// Func:      配置vsa vsg工作流，只是将参数配置，不会开启仪器进行vsa,vsg操作
// Path:      WT_SetVsaVsgControlFlow
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数错误
//              WT_ERR_CODE_GENERAL_ERROR:配置仪器错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: VsaVsgControlFlow * controlFlow: vsa vsg控制流参数
//************************************
FlowTester_DLL_API int CALL_MODE WT_SetVsaVsgControlFlow(int connID, VsaVsgControlFlow *controlFlow);

//************************************
// Method:    WT_SetVsaAnalyzeFrame
// Func:      配置哪个vsa的信号作为分析信号源
// Path:      WT_SetVsaAnalyzeFrame
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数错误或者vsaFlowIndex超过WT_SetVsaVsgControlFlow配置时的数量
//              WT_ERR_CODE_GENERAL_ERROR:配置错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: AlgParameters * alg_param：分析该包信号对应的算法参数
// Parameter: int vsaFlowIndex：vsa流序号，序号从0开始，
//                0：选取VsaVsgControlFlow.vsa_master_control中对应的采集的信号来作为分析信号源，
//                1-n：选取VsaVsgControlFlow.vsa_control_flow_after_master中的0-(n-1)对应的vsa采集的信号来作为分析信号源
//************************************
FlowTester_DLL_API int CALL_MODE WT_SetVsaAnalyzeFrame(int connID, AlgParameters *alg_param, int vsaFlowIndex);

//************************************
// Method:    WT_SetVsaAnalyzeFrameWithRange
// Func:      配置哪个vsa的信号作为分析信号源，并设定信号分析的起始点和结束点
// Path:      WT_SetVsaAnalyzeFrameWithRange
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数错误或者vsaFlowIndex超过WT_SetVsaVsgControlFlow配置时的数量
//              WT_ERR_CODE_GENERAL_ERROR:配置错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: AlgParameters * alg_param：分析该包信号对应的算法参数
// Parameter: int vsaFlowIndex：vsa流序号，序号从0开始，
//                0：选取VsaVsgControlFlow.vsa_master_control中对应的采集的信号来作为分析信号源，
//                1-n：选取VsaVsgControlFlow.vsa_control_flow_after_master中的0-(n-1)对应的vsa采集的信号来作为分析信号源
// Parameter: int frameStartInUs：该包信号分析的起始点，单位，微秒
// Parameter: int validFrameLengthInUs：该包信号分析的长度，单位，微秒
//************************************
FlowTester_DLL_API int CALL_MODE WT_SetVsaAnalyzeFrameWithRange(int connID, AlgParameters *alg_param, int vsaFlowIndex, int frameStartInUs, int validFrameLengthInUs);

//************************************
// Method:    WT_AsynStartVsaVsgFlow
// Func:      异步启动vsa、vsg操作，该步骤将启动仪器根据配置的vsa、vsg流进行vsa、vsg操作
//            该操作为异步操作，当仪器启动vsa、vsg时就会返回，不会等到vsa、vsg结束才返回
// Path:      WT_AsynStartVsaVsgFlow
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数错误
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_VsgInaccuracy:发送功率不准确
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
//************************************
FlowTester_DLL_API int CALL_MODE WT_AsynStartVsaVsgFlow(int connID);

//************************************
// Method:    WT_GetFlowCapturedData
// Func:      获取仪器vsa采集到的信号
// Path:      WT_GetFlowCapturedData
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
//************************************
FlowTester_DLL_API int CALL_MODE WT_GetFlowCapturedData(int connID);

//************************************
// Method:    WT_GetVsaVsgFlowState
// Func:      获取vsa、vsg工作流的状态
// Path:      WT_GetVsaVsgFlowState
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: enum WT_VSA_VSG_FLOW_STATE * state: vsa、vsg状态带出指针.状态详见:enum WT_VSA_VSG_FLOW_STATE
//************************************
FlowTester_DLL_API int CALL_MODE WT_GetVsaVsgFlowState(int connID, enum WT_VSA_VSG_FLOW_STATE *state);

//************************************
// Method:    WT_GetDefaultVsaVsgControlFlow
// Func:      获取默认的vsa、vsg流操作配置参数
// Path:      WT_GetDefaultVsaVsgControlFlow
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:操作成功
// Parameter: VsaVsgControlFlow * controlFlow：传入的VsaVsgControlFlow参数缓存指针
//************************************
FlowTester_DLL_API int CALL_MODE WT_GetDefaultVsaVsgControlFlow(VsaVsgControlFlow *controlFlow);

//************************************
// Method:    WT_GetDefaultAlgParameters
// Func:      根据alg_type 获取对应的算法默认参数
// Path:      WT_GetDefaultAlgParameters
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:操作成功
// Parameter: AlgParameters * algParameters：算法参数缓存传入指针
// Parameter: enum ALG_TYPE alg_type：算法类型，取决于分析哪类信号
//************************************
FlowTester_DLL_API int CALL_MODE WT_GetDefaultAlgParameters(AlgParameters *algParameters, enum ALG_TYPE alg_type);

//************************************
// Method:    WT_StopVsaVsgFlow
// Func:      停止vsa、vsg工作流
// Path:      WT_StopVsaVsgFlow
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
//************************************
FlowTester_DLL_API int CALL_MODE WT_StopVsaVsgFlow(int connID);

FlowTester_DLL_API int CALL_MODE WT_GetFlowResult(int connID);

FlowTester_DLL_API int CALL_MODE WT_GetFlowPow(int connID, int vsaFlowIndex,double *result);

FlowTester_DLL_API int CALL_MODE WT_SetNbiotAnalyzeAlgParam(int connID,AlgParameters *alg_param);


#endif