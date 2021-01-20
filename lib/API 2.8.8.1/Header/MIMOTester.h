//******************************************************************************
//  Created:    2015/02/19   11:42
//  File base:  MIMOTester
//  Copyright:  iTest
//  Version:
//
//  Purpose:    This header file defines the types and definitions used to
//              interface to the WT Tester for MIMO.
//              These APIs also can be used for SISO.
//******************************************************************************

#ifndef __WT_MIMO_Tester_h__
#define __WT_MIMO_Tester_h__


#include "testerCommon.h"

#ifndef _Export
#ifdef _WIN32
#define _Export __declspec(dllexport)
#define _Import __declspec(dllimport)
#else
#define _Export
#define _Import
#endif
#endif

#ifdef _WIN32
#ifdef WT_MIMO_TESTER_DLL_EXPORTS
#define WT_MIMO_DLL_API extern _Export
#else
#ifdef WT_C
// Set this compile switch (WT_C) if running C (using plain export names).
#define WT_MIMO_DLL_API extern
#else
// Do not set this compile switch if running C++ (using decorated export
// names).
#define WT_MIMO_DLL_API extern "C" _Import
#endif
#endif
#else
#ifdef __cplusplus
#define WT_MIMO_DLL_API extern "C" __attribute__ ((visibility ("default")))
#else
#define WT_MIMO_DLL_API __attribute__ ((visibility ("default")))
#endif
#endif

typedef struct
{
	double  freq;                           //VSA载波频率,单位：Hz
	double  max_power[MAX_TESTER_COUNT];    //输入的最大功率,dBm; (最好在实际输出到仪器的功率基础上再加12dB，如果接收功率范围未知，建议事先Auto Range)
	double  smp_time;                       //采样时间,us
	int     rfPort[MAX_TESTER_COUNT];       //指定VSA使用的RF端口

	int     trig_type;                      //触发模式,WT_TRIG_TYPE_ENUM
	double  trig_level;                     //触发电平,与max_power的差距,dB
	double  trig_timeout;                   //触发等待超时,sec（该时间与TimeoutWaiting的时间相互独立）
	double  trig_pretime;                   //触发保留时间,保留触发前若干时间内的数据,us

	int     demod;                          //802.11 分析模式.WT_DEMOD_ENUM
	int     iq_swap;                        //IQ交换(频谱反转). WT_IQ_SWAP_ENUM

	int     ph_corr;                        //802.11 a/g/n/ac 相位跟踪. WT_PH_CORR_ENUM
	int     ch_estimate;                    //802.11 a/g/n/ac 通道估计. WT_CH_EST_ENUM
	int     sym_tim_corr;                   //802.11 a/g/n/ac 时序跟踪. WT_SYM_TIM_ENUM
	int     freq_sync;                      //802.11 a/g/n/ac 频率同步. WT_FREQ_SYNC_ENUM
	int     ampl_track;                     //802.11 a/g/n/ac 幅度跟踪. WT_AMPL_TRACK_ENUM

	int     evm_method_11b;                 //802.11 b EVM方式.  WT_11B_METHOD_ENUM
	int     dc_removal;                     //802.11 b 直流去除. WT_DC_REMOVAL_ENUM
	int     eq_taps;                        //802.11 b 均衡类型. WT_EQ_ENUM
	int     cck_ph_corr;                    //802.11 b 相位跟踪. WT_PH_CORR_11b_ENUM

	int     bt_Rate;                        //Bluetooth速率, WT_BT_DATARATE
	int     bt_packet_type;                 //Bluetooth包类型, WT_BT_PACKETTYPE(默认设置为WT_BT_PACKETTYPE_NULL即可)

	int     TimeoutWaiting;                 //在多连接情况下，等待的最大时间，默认值为8秒，单位sec
} MIMOVsaParameter;

typedef struct
{
	double  freq;                           //VSG载波频率,单位：Hz
	double  power[MAX_TESTER_COUNT];        //VSG功率,dBm
	int     rfPort[MAX_TESTER_COUNT];       //指定VSG使用的RF端口

	int     waveType;                       //Wave类型，WT_SIGNAL_ENUM. SIG_USERFILE: 读取本地wave文件; SIG_TESTERFILE:使用仪器存储的wave文件(WT-208固件版本低于或等于3.0.1.10的不支持该项); (其余选项（除SIG_USERFILE和SIG_TESTERFILE以外的选项）：仅WT-208仪器支持)
	char    *wave;                          //VSG数据文件,如果为null,只更新设备配置，不更新wave文件，不配置repeat和wave_gap
	int     repeat;                         //循环发送次数
	double  wave_gap;                       //两次发送间隔,us

	int     TimeoutWaiting;                 //在多连接情况下，等待的最大时间，默认值为8秒，单位sec
} MIMOVsgParameter;

//******************************************************************************
// Name:      WT_MIMO_InitMaxCaptureTime
// Func:      初始化120MHz采样率下支持的最大采样时长.
//            注意: 该接口为可选调用，如果调用，则需在该文档中其他API之前调用,
//            且此函数只能调用一次.
//            如果没有调用该接口,则默认支持的采样时长为10000us.
// Path:      WT_MIMO_InitMaxCaptureTime
// Access:    public
// Returns:   WT_MIMO_DLL_API void
// Parameter: int maxCaptureTimeUs:  最大采样时长,单位: us(微秒)
//******************************************************************************
WT_MIMO_DLL_API void CALL_MODE WT_MIMO_InitMaxCaptureTime(int maxCaptureTimeUs);

//******************************************************************************
// Name:      WT_MIMO_Initilaze
// Func:      初始化WTtester API处理，注意: 在调用该文档中其他API之前需调用该接口,
//            且此函数只能调用一次.
// Path:      WT_MIMO_Initilaze
// Access:    public
// Returns:   WT_MIMO_DLL_API void
// Parameter: void
//******************************************************************************
WT_MIMO_DLL_API void CALL_MODE WT_MIMO_Initilaze(void);

//******************************************************************************
// Name:      WT_MIMO_Terminate
// Func:      释放WT_MIMO_Ex API处理
//            强烈建议在分析结束之后才调用该接口，否则可能造成其他内存处理出错,
//            且此函数只能调用一次.
// Path:      WT_MIMO_Terminate
// Access:    public
// Returns:   WT_MIMO_DLL_API void
// Parameter: void
//******************************************************************************
WT_MIMO_DLL_API void CALL_MODE WT_MIMO_Terminate(void);

//******************************************************************************
// Name:      WT_MIMO_Connect4Tester
// Func:      连接指定的4台测试仪(WTtester)
// Path:      WT_MIMO_Connect4Tester
// Access:    public
// Returns:   WT_MIMO_DLL_API int：
//                WT_ERR_CODE_CODE_OK:操作成功
//                WT_ERR_CODE_CODE_CONNECT_FAIL:连接失败
// Parameter: char * ipAddr1:  测试仪IP地址，例如ipAddr1="192.168.10.1"
// Parameter: char * ipAddr2:  测试仪IP地址，例如ipAddr2="192.168.10.2"
// Parameter: char * ipAddr3:  测试仪IP地址，例如ipAddr3="192.168.10.3"
// Parameter: char * ipAddr4:  测试仪IP地址，例如ipAddr4="192.168.10.4"
// Parameter: int * connID：   连接ID标识, 用于后面对此连接操作识别.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_Connect4Tester(char *ipAddr1, char *ipAddr2, char *ipAddr3, char *ipAddr4, int *connID);

//******************************************************************************
// Name:      WT_MIMO_Connect3Tester
// Func:      连接指定的3台测试仪(WTtester)
// Path:      WT_MIMO_Connect3Tester
// Access:    public
// Returns:   WT_MIMO_DLL_API int：
//                WT_ERR_CODE_CODE_OK:操作成功
//                WT_ERR_CODE_CODE_CONNECT_FAIL:连接失败
// Parameter: char * ipAddr1:  测试仪IP地址，例如ipAddr1="192.168.10.1"
// Parameter: char * ipAddr2:  测试仪IP地址，例如ipAddr2="192.168.10.2"
// Parameter: char * ipAddr3:  测试仪IP地址，例如ipAddr3="192.168.10.3"
// Parameter: int * connID：   连接ID标识, 用于后面对此连接操作识别.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_Connect3Tester(char *ipAddr1, char *ipAddr2, char *ipAddr3, int *connID);

//******************************************************************************
// Name:      WT_MIMO_Connect2Tester
// Func:      连接指定的2台测试仪(WTtester)
// Path:      WT_MIMO_Connect2Tester
// Access:    public
// Returns:   int：
//                WT_ERR_CODE_CODE_OK:操作成功
//                WT_ERR_CODE_CODE_CONNECT_FAIL:连接失败
// Parameter: char * ipAddr1:  测试仪IP地址，例如ipAddr1="192.168.10.1"
// Parameter: char * ipAddr2:  测试仪IP地址，例如ipAddr2="192.168.10.2"
// Parameter: int * connID：   连接ID标识, 用于后面对此连接操作识别.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_Connect2Tester(char *ipAddr1, char *ipAddr2, int *connID);

//******************************************************************************
// Name:      WT_MIMO_Connect1Tester
// Func:      连接指定的1台测试仪(WTtester)
// Path:      WT_MIMO_Connect1Tester
// Access:    public
// Returns:   WT_MIMO_DLL_API int：
//                WT_ERR_CODE_CODE_OK:操作成功
//                WT_ERR_CODE_CODE_CONNECT_FAIL:连接失败
// Parameter: char * ipAddr1:  测试仪IP地址，例如ipAddr1="192.168.10.1"
// Parameter: int * connID：   连接ID标识, 用于后面对此连接操作识别.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_Connect1Tester(char *ipAddr, int *connID);

//******************************************************************************
// Name:      WT_SwitchedMIMOConnect
// Func:      Switched MIMO 场景的连接
// Path:      WT_SwitchedMIMOConnect
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//                WT_ERR_CODE_CODE_OK:操作成功
//                WT_ERR_CODE_CODE_CONNECT_FAIL:连接失败
// Parameter: char * ipAddr:  测试仪IP地址，例如ipAddr1="192.168.10.1"
// Parameter: int * connID：   连接ID标识, 用于后面对此连接操作识别.
// Parameter: int antennaCount:  DUT天线连接仪器的天线数
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_SwitchedMIMOConnect(char *ipAddr, int *connID, int antennaCount);

//******************************************************************************
// Name:      WT_MIMO_DisConnect
// Func:      断开连接，释放该连接所占用的所有资源
// Path:      WT_MIMO_DisConnect
// Access:    public
// Returns:   WT_MIMO_DLL_API void
// Parameter: int connID: 连接时获取的ID标识.
//******************************************************************************
WT_MIMO_DLL_API void CALL_MODE WT_MIMO_DisConnect(int connID);

//******************************************************************************
// Name:      WT_MIMO_GetDefaultParameter
// Func:      充填默认的VSA参数到mimoVsaParam,  VSG参数到mimoVsgParam，
//            建议在设置VSA，VSG之前先执行该操作，之后再在此基础上进行修改
// Path:      WT_MIMO_GetDefaultParameter
// Access:    public
// Returns:   WT_MIMO_DLL_API int:
//               WT_ERR_CODE_OK: 操作成功
//               WT_ERR_CODE_UNKNOW_PARAMETER：无效的参数
// Parameter: MIMOVsaParameter * mimoVsaParam:  MIMO_VSA详细参数
// Parameter: MIMOVsgParameter * mimoVsgParam:  MIMO_VSG详细参数
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetDefaultParameter(MIMOVsaParameter *mimoVsaParam, MIMOVsgParameter *mimoVsgParam);

//******************************************************************************
// Name:      WT_MIMO_SetExternalGain
// Func:      设置(PC与WTtester间的)外部增益，同时对VSA以及VSG生效
// Path:      WT_MIMO_SetExternalGain
// Access:    public
// Returns:   WT_MIMO_DLL_API int:
//                WT_ERR_CODE_OK: 操作成功
//                WT_ERR_CODE_UNKNOW_PARAMETER: 参数有误
//                WT_ERR_CODE_CONNECT_FAIL: 连接未建立或已中断
// Parameter: int connID: 连接时获取的ID标识
// Parameter: double * extGain: 外部增益值数组，单位dB，按顺序对应所连接的仪器，
//                             注意:此处为外部增益，并非外部衰减。
//                             强烈建议使用实际增益值，该值设置过大可能会导致VSA或VSG结果异常.
// Parameter: int extGainLen: extGain数组的长度（一般为需要配置的仪器数）
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetExternalGain(int connID, double *extGain, int extGainLen);


//******************************************************************************
// Name:      WT_MIMO_SetVSA
// Func:      设置MIMO_VSA参数
// Path:      WT_MIMO_SetVSA
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//               WT_ERR_CODE_OK:操作成功
//               WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//               WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//               WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: MIMOVsaParameter * vsaParam: MIMO_VSA详细参数
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetVSA(int connID, MIMOVsaParameter *vsaParam);

//******************************************************************************
// Name:      WT_MIMO_SetVSG
// Func:      设置MIMO_VSG参数
// Path:      WT_MIMO_SetVSG
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//               WT_ERR_CODE_OK:操作成功
//               WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//               WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//               WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: MIMOVsgParameter * vsgParam: MIMO_VSA详细配置参数
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetVSG(int connID, MIMOVsgParameter *vsgParam);

//******************************************************************************
// Name:      WT_MIMO_SetVSA_AutoRange
// Func:      根据VSA参数，自动匹配参考电平值(Max Power Level),并在匹配成功之后配置到WTtester中去
//            强烈建议在输入信号未知的前提下，优先使用该接口
// Path:      WT_MIMO_SetVSA_AutoRange
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//               WT_ERR_CODE_OK:操作成功
//               WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//               WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//               WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//               WT_ERR_CODE_TIMEOUT:操作超时
//               WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: MIMOVsaParameter * vsaParam: MIMO_VSA详细参数，在配置成功之后，会返回新的参考电平值
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetVSA_AutoRange(int connID, MIMOVsaParameter *vsaParam);

//******************************************************************************
// Name:      WT_MIMO_DataCapture
// Func:      按照指定的VSA参数进行数据抓取
// Path:      WT_MIMO_DataCapture
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_DataCapture(int connID);

//******************************************************************************
// Name:      WT_MIMO_StopDataCapture
// Func:      停止采集数据
// Path:      WT_MIMO_StopDataCapture
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_StopDataCapture(int connID);

//******************************************************************************
// Name:      WT_MIMO_GetResult
// Func:      获取指定parameter的分析结果，获取成功后，各输出参数值才有效.
//              注意:该步骤的前提为已经抓取到了相关数据(事先调用接口DataCapture)
// Path:      WT_MIMO_GetResult
// Access:    public
// Returns:   int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_NO_DATA_CAPTURED:未抓取数据
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char * anaParmString: 结果类型(字符串类型)，例如WT_RES_EVM_ALL
// Parameter: double * result: 对应结果存储数组
// Parameter: int resultLength: result数组长度（一般为所需要获取结果的仪器数）
// Parameter: char * description: 该组结果值的对应描述
// Parameter: char * unit: 该组结果值的对应的单位
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetResult(int connID, char *anaParmString, double *result, int resultLength, char *description, char *unit);

//******************************************************************************
// Name:      WT_MIMO_GetVectorResult
// Func:      获取指定parameter的分析结果，获取成功后，各输出参数值才有效.
//              注意:该步骤的前提为已经抓取到了相关数据(事先调用接口DataCapture)，该结果项以数组的形式呈现
// Path:      WT_MIMO_GetVectorResult
// Access:    public
// Returns:   WT_MIMO_DLL_API int: 返回实际复制到结果存储区的数目，单元大小以输入的resultType为准，返回0代表参数错误或者分析失败
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int streamIndex：第几条流..从0开始
// Parameter: char * anaParmString：结果类型(字符串类型)，例如WT_RES_EVM_ALL.
// Parameter: void * result: 对应结果的存储地址.
// Parameter: int resultType：对应结果（result）的数据类型，参见 WT_RESULT_DATA_TYPE.
// Parameter: int resultSize：对应结果（result）存储区域的大小.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetVectorResult(int connID, int streamIndex, char *anaParmString, void *result, int resultType, int resultSize);

//******************************************************************************
// Name:      WT_MIMO_GetVectorResultElementSize
// Func:      获取结果中每个单元数据的大小，单位：字节
// Path:      WT_MIMO_GetVectorResultElementSize
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_NO_DATA_CAPTURED:未抓取数据
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char * anaParmString：结果类型(字符串类型)，例如WT_RES_EVM_ALL.
// Parameter: int * elementSize：输出单元数据的大小
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetVectorResultElementSize(int connID, char *anaParmString, int *elementSize);

//******************************************************************************
// Name:      WT_MIMO_GetVectorResultElementCount
// Func:      获取整个分析结果的长度
// Path:      WT_MIMO_GetVectorResultElementCount
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_NO_DATA_CAPTURED:未抓取数据
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char * anaParmString：结果类型(字符串类型)，例如WT_RES_EVM_ALL.
// Parameter: int * elementCount：输出结果的长度
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetVectorResultElementCount(int connID, char *anaParmString, int *elementCount);

//******************************************************************************
// Name:      WT_MIMO_StartVSG
// Func:      按照指定的VSG参数进行信号(wave)发送，并在发送完成后才返回(同步进行)
//             注意：当发送次数设为0（无限次时）,该API会阻塞进行，不会退出
// Path:      WT_MIMO_StartVSG
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_TxInaccuracy:TX功率不准确
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_StartVSG(int connID);

//******************************************************************************
// Name:      WT_MIMO_AsynStartVSG
// Func:      按照指定的VSG参数进行信号(wave)发送，并在命令下发后直接返回(异步进行)
// Path:      WT_MIMO_AsynStartVSG
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_TxInaccuracy:发送功率不准确
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_AsynStartVSG(int connID);

//******************************************************************************
// Name:      WT_MIMO_GetVSGCurrentState
// Func:      获取VSG当前状态.
// Path:      WT_MIMO_GetVSGCurrentState
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int * state: VSG状态带出指针.VSG状态详见:enum WT_VSG_STATE
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetVSGCurrentState(int connID, int *state);

//******************************************************************************
// Name:      WT_MIMO_StopVSG
// Func:      停止VSG.
// Path:      WT_MIMO_StopVSG
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_StopVSG(int connID);

//******************************************************************************
// Name:      WT_MIMO_GetTesterVersion
// Func:      获取对应的测试仪的版本以及测试仪类型.
// Path:      WT_MIMO_GetTesterVersion
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL: 连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: u32BufSize大小不够，或者还未连接指定的测试仪
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int index: 第几台仪器，从0开始
// Parameter: TesterInfo * buffer:装载版本信息的容器,装载结果详见stTesterInfo
// Parameter: int * bufferSize: 指定容器的大小
// Parameter: int * testerType：仪器类型,详见WT_TESTER_TYPE
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetTesterVersion(int connID, int index, TesterInfo *buffer, int bufferSize, int *testerType);

//******************************************************************************
// Name:      WT_MIMO_GetTesterSpecification
// Func:      获取仪器规格
// Path:      WT_MIMO_GetTesterSpecification
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: testerSpec 为空
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int index: 第几台仪器，从0开始
// Parameter: DeviceSpecification * testerSpec：Tester规格存放地址
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetTesterSpecification(int connID, int index, DeviceSpecification *testerSpec);
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetTesterSpecification208C(int connID, int index, Device208CSpecification *testerSpec);

//******************************************************************************
// Name:      WT_MIMO_GetTesterConnStataus
// Func:      用于查看仪器连接状态.
//              注意：
//              针对以太网使用，设备存在以下3种状态:
//              case 1:
//              BUSY:IP:192.168.10.2;PORT:28691;
//                  表示设备正被192.168.10.2的28691端口使用
//              case 2:
//              ERR:DEVICE DOES NOT EXIST
//                      无法连接ipAddr指定的设备
//              case 3:
//              IDLE:
//                  设备处于空闲状态
// Path:      WT_MIMO_GetTesterConnStataus
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              0:网络无法连接
//              !0:pu8Buf装载的有效数据的长度
// Parameter: char * ipAddr: 字符串，装载目标设备IP，如"192.168.10.254"
// Parameter: char * buffer: 返回操作结果，字符串，由设备生成返回.
// Parameter: int bufferSize: buffer的大小
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetTesterConnStataus(char *ipAddr, char *buffer, int bufferSize);

//******************************************************************************
// Name:      WT_MIMO_SetBandwidthMode
// Func:      设置带宽识别模式
// Path:      WT_MIMO_SetBandwidthMode
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER：参数有误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int bandwidthDetect: 带宽模式, 参考 WT_BANDWIDTH_DETECT_ENUM 枚举
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetBandwidthMode(int connID, int bandwidthDetect);

//******************************************************************************
// Name:      WT_MIMO_SetZigBeeAnalysisOptimise
// Func:      ZigBee分析优化选项
// Path:      WT_MIMO_SetZigBeeAnalysisOptimise
// Access:    public
// Returns:   int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER：参数有误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int AnalysisOptimise: 分析优化开关, 参考 WT_ZB_ANALYSIS_OPTIMISE_ENUM 枚举
//              WT_ZB_ANALYSIS_OPTIMISE_DISABLED == 0;
//              WT_ZB_ANALYSIS_OPTIMISE_ENABLED  == 1;
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetZigBeeAnalysisOptimise(int connID, int AnalysisOptimise);

//******************************************************************************
// Name:      WT_MIMO_GetSymbolsEvm
// Func:      获取某段Symbol范围内的Evm均值
// Path:      WT_MIMO_GetSymbolsEvm
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER：参数有误
//              WT_ERR_CODE_GENERAL_ERROR：获取结果失败
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int streamIndex: 第几条流, 从0开始.
// Parameter: int startSymbol: 起始Symbol序号，从0开始.
// Parameter: int endSymbol: 结束Symbol序号，计算时不包含该Symbol.
// Parameter: int evmResultType: 设定取哪种类型的evm结果，参照enum SYMBOLS_EVM_RESULT_TYPE.
// Parameter: double * evmResult(Out): 存储规定Symbol范围内的Evm均值的缓存，单位dB.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetSymbolsEvm(int connID, int streamIndex, int startSymbol, int endSymbol, int evmResultType, double *evmResult);

//******************************************************************************
// Name:      WT_MIMO_DataStore
// Func:      保存Vsa信号数据
// Path:      WT_MIMO_DataStore
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_GENERAL_ERROR: 保存失败
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char * fileName：存储的文件名
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_DataStore(int connID, char *fileName);

//******************************************************************************
// Name:      WT_MIMO_AnalyzeCmimoReferenceData
// Func:      CMIMO场景下分析DUT单天线发出信号的参考数据
// Path:      WT_MIMO_AnalyzeCmimoReferenceData
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: antenna配置超过3或小于0
//              WT_ERR_CODE_GENERAL_ERROR: 分析失败，原因可能是还没抓取数据或抓取的数据有问题
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int antenna：第几根天线，从0开始（0-3）
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_AnalyzeCmimoReferenceData(int connID, int antenna);

//************************************
// Method:    WT_MIMO_GetCmimoResult
// Func:      获取CMIMO分析的相关结果
// Path:      WT_MIMO_GetCmimoResult
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: antenna配置超过3或小于0
//              WT_ERR_CODE_GENERAL_ERROR: 分析失败，原因可能是还没有对应参考文件或者是抓取的数据有问题
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int streamIndex: 第几条流, 从0开始
// Parameter: char * anaParmString(in)：结果类型(字符串类型)，例如WT_RES_EVM_ALL
// Parameter: double * result(out)：对应结果值
// Parameter: char * description(out)：该结果值的对应描述
// Parameter: char * unit(out)：该结果值的对应的单位
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetCmimoResult(int connID, int streamIndex, char *anaParmString, double *cmimoResult, char *description, char *unit);

//******************************************************************************
// Name:      WT_MIMO_LoadCmimoReferenceData
// Func:      CMIMO场景下，加载信号对应的参考文件
// Path:      WT_MIMO_LoadCmimoReferenceData
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: pu8FileName为空
//              WT_ERR_CODE_GENERAL_ERROR: 加载失败，原因可能是文件格式不对
// Parameter: int connID(in): 连接时获取的ID标识.
// Parameter: char * pu8FileName(in): 加载的文件名（包含路径）
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_LoadCmimoReferenceData(int connID, char *pu8FileName);

//******************************************************************************
// Name:      WT_MIMO_SaveCmimoReferenceData
// Func:      CMIMO场景下保存信号对应的参考数据
//            注：需要之前成功生成参考数据
// Path:      WT_MIMO_SaveCmimoReferenceData
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: pu8FileName为空
//              WT_ERR_CODE_GENERAL_ERROR: 保存失败，原因可能是文件格式不对
// Parameter: int connID(in): 连接时获取的ID标识.
// Parameter: char * pu8FileName(in): 保存的文件名（包含路径）
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SaveCmimoReferenceData(int connID, char *pu8FileName);

//************************************
// Method:    WT_MIMO_SetSpectrumMaskErrorAnalyzeRange
// Func:      设置频谱模板错误率分析的范围，默认全频段分析，
//            比如要分析中间40M带宽范围的频谱错误率，startFrequency设为-20，endFrequency设为20
// Path:      WT_MIMO_SetSpectrumMaskErrorAnalyzeRange
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int channelIndex: 需要分析的仪器通道序号，如需要分析第1台仪器采到的信号，该值则设为0
// Parameter: int startFrequency：分析的起始频率值
// Parameter: int endFrequency：分析的结束频率值
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetSpectrumMaskErrorAnalyzeRange(int connID, int channelIndex, int startFrequency, int endFrequency);

//************************************
// Method:    WT_MIMO_SetSpectrumMaskVersion
// Func:      设置频谱模板版本，只适用于11n
// Path:      WT_MIMO_SetSpectrumMaskVersion
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: version为参数错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int version：频谱模板版本，对应枚举SPECTRUM_MASK_VERSION
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetSpectrumMaskVersion(int connID, int version);

//************************************
// Method:    WT_MIMO_SetAnalyzeFrameIndex
// Func:      设置分析第几帧信号
// Path:      WT_MIMO_SetAnalyzeFrameIndex
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: 参数错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int analyzeFrameIndex：第几帧信号，从0开始
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetAnalyzeFrameIndex(int connID, int analyzeFrameIndex);

//************************************
// Method:    WT_MIMO_SetZWaveRate
// Func:      设置ZWave速率
// Path:      WT_MIMO_SetZWaveRate
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: zWaveRate参数错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int zWaveRate：ZWave Rate，对应枚举ZWAVE_RATE_ENUM
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetZWaveRate(int connID, int zWaveRate);

//************************************
// Method:    WT_MIMO_ExecInternalCmd
// Func:      执行内部命令
// Path:      WT_MIMO_ExecInternalCmd
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: zWaveRate参数错误
// Parameter: char *ipAddr: 字符串，装载目标设备IP，如"192.168.10.254"
// Parameter: char *cmd: 需要执行的命令.
// Parameter: int cmdLen：命令长度.
// Parameter: char *buffer: 结果缓存.
// Parameter: char *bufferSize: 缓存大小.
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_ExecInternalCmd(char *ipAddr, char *cmd, int cmdLen, char *buffer, int bufferSize);

//************************************
// Method:    WT_MIMO_SetLrwpanFskAnalyzeParam
// Func:      设置LrwpanFsk分析参数
// Path:      WT_MIMO_SetLrwpanFskAnalyzeParam
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: pLrwpanFskParam参数错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: LrwpanFskParam *pLrwpanFskParam：LrwpanFsk分析参数
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetLrwpanFskAnalyzeParam(int connID, LrwpanFskParam *pLrwpanFskParam);

//************************************
// Method:    WT_MIMO_AuthenGet
// Func:      获取认证字符，只对WT208H生效
// Path:      WT_MIMO_AuthenGet
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER：参数有误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char *buffer：保存认证字符的缓存
// Parameter: int bufferSize：缓存大小
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_AuthenGet(int connID, char *buffer, int bufferSize);

//************************************
// Method:    WT_MIMO_AuthenSet
// Func:      下发加密后的字符，只对WT208H生效
// Path:      WT_MIMO_AuthenSet
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确，认证通过
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER：参数有误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char *buffer：保存加密字符的缓存
// Parameter: int dataLen：加密字符长度
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_AuthenSet(int connID, char *buffer, int bufferSize);

#endif

