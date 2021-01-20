//******************************************************************************
//  Created:    2014/11/19   11:42
//  File base:  tester
//  Copyright:  iTest
//  Version:
//
//  Purpose:    This header file defines the types and definitions used to
//              interface to the WT tester.
//******************************************************************************

#ifndef __WTtester_h__
#define __WTtester_h__

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
#ifdef WTtester_DLL_EXPORTS
#define WTtester_DLL_API extern _Export
#else
#ifdef WT_C
// Set this compile switch (WT_C) if running C (using plain export names).
#define WTtester_DLL_API extern
#else
// Do not set this compile switch if running C++ (using decorated export
// names).
#define WTtester_DLL_API extern "C" _Import
#endif
#endif
#else
#ifdef __cplusplus
#define WTtester_DLL_API extern "C" __attribute__ ((visibility ("default")))
#else
#define WTtester_DLL_API __attribute__ ((visibility ("default")))
#endif
#endif

typedef struct
{
	double  freq;               //VSA载波频率,单位：Hz
	double  max_power;          //输入的最大功率,dBm; (最好在实际输出到仪器的功率基础上再加12dB，如果接收功率范围未知，建议事先Auto Range)
	double  smp_time;           //采样时间,us
	int     rfPort;             //指定VSA使用的RF端口

	int     trig_type;          //触发模式,WT_TRIG_TYPE_ENUM
	double  trig_level;         //触发电平,与max_power的差距,dB
	double  trig_timeout;       //触发等待超时,sec（该时间与TimeoutWaiting的时间相互独立）
	double  trig_pretime;       //触发保留时间,保留触发前若干时间内的数据,us

	int     demod;              //802.11 分析模式.WT_DEMOD_ENUM
	int     iq_swap;            //IQ交换(频谱反转). WT_IQ_SWAP_ENUM

	int     ph_corr;            //802.11 a/g/n/ac 相位跟踪. WT_PH_CORR_ENUM
	int     ch_estimate;        //802.11 a/g/n/ac 通道估计. WT_CH_EST_ENUM
	int     sym_tim_corr;       //802.11 a/g/n/ac 时序跟踪. WT_SYM_TIM_ENUM
	int     freq_sync;          //802.11 a/g/n/ac 频率同步. WT_FREQ_SYNC_ENUM
	int     ampl_track;         //802.11 a/g/n/ac 幅度跟踪. WT_AMPL_TRACK_ENUM

	int     evm_method_11b;     //802.11 b EVM方式.  WT_11B_METHOD_ENUM
	int     dc_removal;         //802.11 b 直流去除. WT_DC_REMOVAL_ENUM
	int     eq_taps;            //802.11 b 均衡类型. WT_EQ_ENUM
	int     cck_ph_corr;        //802.11 b 相位跟踪. WT_PH_CORR_11b_ENUM

	int     bt_Rate;            //Bluetooth速率, WT_BT_DATARATE
	int     bt_packet_type;     //Bluetooth包类型, WT_BT_PACKETTYPE(默认设置为WT_BT_PACKETTYPE_NULL即可)

	int     TimeoutWaiting;     //在多连接情况下，等待的最大时间，默认值为8秒，单位sec

} VsaParameter;

typedef struct
{
	double  freq;               //VSG载波频率,单位：Hz
	double  power;              //VSG功率,dBm
	int     rfPort;             //指定VSG使用的RF端口

	int     waveType;           //Wave类型，WT_SIGNAL_ENUM. SIG_USERFILE: 读取本地wave文件; SIG_TESTERFILE: 使用仪器存储的wave文件(WT-208固件版本低于或等于3.0.1.10的不支持该项); (其余选项（除SIG_USERFILE和SIG_TESTERFILE以外的选项）：仅WT-208仪器支持)
	char    *wave;              //VSG数据文件,如果为null,只更新设备配置，不更新wave文件，不配置repeat和wave_gap
	int     repeat;             //循环发送次数
	double  wave_gap;           //两次发送间隔，us

	int     TimeoutWaiting;     //在多连接情况下，等待的最大时间，默认值为8秒，单位sec
} VsgParameter;

//******************************************************************************
// Name:      WT_InitMaxCaptureTime
// Func:      初始化120MHz采样率下支持的最大采样时长.
//            注意: 该接口为可选调用，如果调用，则需在该文档中其他API之前调用,
//            且此函数只能调用一次.
//            如果没有调用该接口,则默认支持的采样时长为10000us.
// Path:      WT_InitMaxCaptureTime
// Access:    public
// Returns:   WTtester_DLL_API void
// Parameter: int maxCaptureTimeUs:  最大采样时长,单位: us(微秒)
//******************************************************************************
WTtester_DLL_API void CALL_MODE WT_InitMaxCaptureTime(int maxCaptureTimeUs);

//******************************************************************************
// Name:      WT_DLLInitialize
// Func:      初始化WTtester API处理，注意: 在调用该文档中其他API之前需调用该接口,
//            且此函数只能调用一次.
// Path:      WT_DLLInitialize
// Access:    public
// Returns:   WTtester_DLL_API void
// Parameter: void
//******************************************************************************
WTtester_DLL_API void CALL_MODE WT_DLLInitialize(void);

//******************************************************************************
// Name:      WT_DLLTerminate
// Func:      释放WTtester API处理
//            注：强烈建议在所有操作结束之后才调用该接口，否则可能造成其他内存处理出错,
//            且此函数只能调用一次.
// Path:      WT_DLLTerminate
// Access:    public
// Returns:   WTtester_DLL_API void
// Parameter: void
//******************************************************************************
WTtester_DLL_API void CALL_MODE WT_DLLTerminate(void);

//******************************************************************************
// Name:      WT_Connect
// Func:      连接指定测试仪(WTtester)
//            该接口不会强制抢断指定测试仪与其他EXE之间的连接
//            连接WT-208时，最多同时存在4个连接；其余测试仪仅支持1个连接
//            连接任何仪器时，如果指定测试已经被WLAN Meter连接，则该接口无法创建新的连接
//            连接失败时，可以通过WT_GetTesterConnStataus查询失败原因
// Path:      WT_Connect
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: char * ipAddr
//              ipAddr:测试仪IP地址，例如"192.168.10.254"
// Parameter: int * connID
//              connID: 连接ID标识, 用于后面对此连接操作识别.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_Connect(char *ipAddr, int *connID);

//******************************************************************************
// Name:      WT_ForceConnect
// Func:      强制连接到测试仪
// Path:      WT_ForceConnect
// Access:    public
// Returns:   WTtester_DLL_API int
//             WT_ERR_CODE_OK
//             WT_ERR_CODE_CONNECT_FAIL
// Parameter: char * ipAddr:测试仪IP地址，例如"192.168.10.254"
// Parameter: int * connID: 连接ID标识, 用于后面对此连接操作识别.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_ForceConnect(char *ipAddr, int *connID);

//******************************************************************************
// Name:      WT_DisConnect
// Func:      断开连接，释放该连接所占用的所有资源
// Path:      WT_DisConnect
// Access:    public
// Returns:   WTtester_DLL_API void
// Parameter: int connID
//              connID: 连接时获取的ID标识.
//******************************************************************************
WTtester_DLL_API void CALL_MODE WT_DisConnect(int connID);

//******************************************************************************
// Name:      WT_GetDefaultParameter
// Func:      充填默认的VSA参数到vsaParam,  VSG参数到vsgParam，
//            建议在设置VSA,VSG之前先执行该操作，之后再在此基础上进行修改
// Path:      WT_GetDefaultParameter
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: VsaParameter * vsaParam
//              VSA详细参数
// Parameter: VsgParameter * vsgParam
//              VSG详细参数(repeat以及wave_gap部分不会更新).
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetDefaultParameter(VsaParameter *vsaParam, VsgParameter *vsgParam);

//******************************************************************************
// Name:      WT_SetExternalGain
// Func:      设置(DUT与WTtester间的)外部增益，同时对VSA以及VSG生效
// Path:      WT_SetExternalGain
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: double extGain
//              extGain: 外部增益值，单位dB，
//              注意:此处为外部增益，并非外部衰减。
//              强烈建议使用实际增益值，该值设置过大可能会导致VSA或VSG结果异常.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetExternalGain(int connID, double extGain);

//******************************************************************************
// Name:      WT_GetExternalGain
// Func:      获取(DUT与WTtester间的)外部增益，较线时使用
// Path:      WT_GetExternalGain
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: CableVerifyParameter * param
//              param:  较线参数
// Parameter: double * extGain
//              extGain: 外部增益值，单位dB，
//              注意:此处为外部增益，并非外部衰减。在使用该接口之后，
//              若需还原到正常的测试，需重新WT_SetVSA/WT_SetVSG
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetExternalGain(int connID, CableVerifyParameter *param, double *extGain);

//******************************************************************************
// Name:      WT_SetVSA
// Func:      设置VSA参数
// Path:      WT_SetVSA
// Access:    public
// Returns:   WTtester_DLL_API int
//WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: VsaParameter * vsaParam
//              vsaParam: VSA详细参数
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetVSA(int connID, VsaParameter *vsaParam);

//******************************************************************************
// Name:      WT_SetVSG
// Func:      设置VSG参数，
//              注意：调用该参数之后如果指定的波形文件有效，会停止VSG,有需要的话需重新开启
//              如果指定的波形文件无效或者参数vsgParam为空，会返回WT_ERR_CODE_UNKNOW_PARAMETER，且不影响之前的VSG状态
// Path:      WT_SetVSG
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: VsgParameter * vsgParam
//              vsgParam: VSG详细参数
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetVSG(int connID, VsgParameter *vsgParam);

//******************************************************************************
// Name:      WT_SetVSA_AutoRange
// Func:      根据VSA参数，自动匹配参考电平值(Max Power Level),并在匹配成功之后配置到WTtester中去
//              强烈建议在输入信号未知的前提下，优先使用该接口
//
//              如果输入到仪器的信号间隔(IFG)大于200ms，或者信号功率跳变非常大时，可能会导致Auto Range返回的参考电平不准确
// Path:      WT_SetVSA_AutoRange
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: VsaParameter * vsaParam
//              vsaParam: VSA详细参数，在配置成功之后，会返回新的参考电平值
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetVSA_AutoRange(int connID, VsaParameter *vsaParam);

//******************************************************************************
// Name:      WT_DataCapture
// Func:      按照指定的VSA参数进行数据抓取
// Path:      WT_DataCapture
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID
//              connID: 连接时获取的ID标识.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_DataCapture(int connID);

//******************************************************************************
// Name:      WT_StopDataCapture
// Func:      停止采集数据
// Path:      WT_StopDataCapture
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connId: 连接时获取的ID标识.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_StopDataCapture(int connID);

//******************************************************************************
// Name:      WT_GetResult
// Func:      获取指定parameter的分析结果，获取成功后，各输出参数值才有效.
//              注意:该步骤的前提为已经抓取到了相关数据(事先调用接口DataCapture)
// Path:      WT_GetResult
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_NO_DATA_CAPTURED:未抓取数据
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: char * anaParmString
//              结果类型(字符串类型)，例如WT_RES_EVM_ALL
// Parameter: double * result
//              result: 对应结果值
// Parameter: char * description
//              description: 该结果值的对应描述
// Parameter: char * unit
//              unit: 该结果值的对应的单位
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetResult(int connID, char *anaParmString, double *result, char *description, char *unit);

//******************************************************************************
// Name:      WT_GetVectorResultElementSize
// Func:      获取结果中每个单元数据的大小，单位：字节
// Path:      WT_GetVectorResultElementSize
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_NO_DATA_CAPTURED:未抓取数据
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char * anaParmString：结果类型(字符串类型)，例如WT_RES_EVM_ALL
// Parameter: int * elementSize：输出单元数据的大小
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetVectorResultElementSize(int connID, char *anaParmString, int *elementSize);

//******************************************************************************
// Name:      WT_GetVectorResultElementCount
// Func:      获取整个结果的长度
// Path:      WT_GetVectorResultElementCount
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_NO_DATA_CAPTURED:未抓取数据
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
//              WT_ERR_CODE_OUT_OF_MEMORY:内存不足
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char * anaParmString：结果类型(字符串类型)，例如WT_RES_EVM_ALL
// Parameter: int * elementCount：输出结果的长度
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetVectorResultElementCount(int connID, char *anaParmString, int *elementCount);

//******************************************************************************
// Name:      WT_GetVectorResult
// Func:      获取指定parameter的分析结果，获取成功后，各输出参数值才有效.
//              注意:该步骤的前提为已经抓取到了相关数据(事先调用接口DataCapture)，该结果项以数组的形式呈现
// Path:      WT_GetVectorResult
// Access:    public
// Returns:   WTtester_DLL_API int: 返回实际复制到结果的数目，单元大小以输入的resultType为准，返回0代表参数错误或者分析失败
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char * anaParmString：结果类型(字符串类型)，例如enum WT_RES_EVM_ALL
// Parameter: void * result: 对应结果存储区域
// Parameter: int resultType：结果的数据类型，参考WT_RESULT_DATA_TYPE
// Parameter: int resultSize：结果存储区域大小，单位：字节
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetVectorResult(int connID, char *anaParmString, void *result, int resultType, int resultSize);

//******************************************************************************
// Name:      WT_StartVSG
// Func:      按照指定的VSG参数进行信号(wave)发送，并在发送完成后才返回(同步进行)
// Path:      WT_StartVSG
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_VsgInaccuracy:VSG功率不准确
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID
//              connID: 连接时获取的ID标识.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_StartVSG(int connID);

//******************************************************************************
// Name:      WT_AsynStartVSG
// Func:      按照指定的VSG参数进行信号(wave)发送，并在命令下发后直接返回(异步进行)
// Path:      WT_AsynStartVSG
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_VsgInaccuracy:发送功率不准确
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID
//              connID: 连接时获取的ID标识.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_AsynStartVSG(int connID);

//******************************************************************************
// Name:      WT_GetVSGCurrentState
// Func:      获取VSG当前状态.
// Path:      WT_GetVSGCurrentState
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_TIMEOUT:操作超时
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: int * state
//              state: VSG状态带出指针.VSG状态详见:enum WT_VSG_STATE
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetVSGCurrentState(int connID, int *state);

//******************************************************************************
// Name:      WT_StopVSG
// Func:      停止VSG.
// Path:      WT_StopVSG
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_GENERAL_ERROR:其他错误
// Parameter: int connID
//              connID: 连接时获取的ID标识.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_StopVSG(int connID);

//******************************************************************************
// Name:      WT_SetWT208NetInfo
// Func:      设置WT208的几个子网口使用信息.
// Path:      WT_SetWT208NetInfo
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER:参数有误
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: WT_208_NET_TYPE * ipAddrs
//              ipAddrs: 各网口的配置信息
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetWT208NetInfo(int connID, WT_208_NET_TYPE *ipAddrs);
WTtester_DLL_API int CALL_MODE WT_SetVirtualSubNetInfo(int connID, WT_VIRTUAL_NET_TYPE *ipAddrs);
//******************************************************************************
// Name:      WT_GetTesterVersion
// Func:      获取测试仪的版本以及测试仪类型.
// Path:      WT_GetTesterVersion
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER:u32BufSize大小不够，或者还未连接指定的测试仪
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: TesterInfo * buffer
//              buffer:装载版本信息的容器,装载结果详见TesterInfo
// Parameter: int bufferSize
//              bufferSize: 指定容器的大小
// Parameter: int * testerType
//              testerType：仪器类型,详见WT_TESTER_TYPE
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetTesterVersion(int connID, TesterInfo *buffer, int bufferSize, int *testerType);

//******************************************************************************
// Name:      WT_GetTesterSpecification
// Func:      获取仪器规格
// Path:      WT_GetTesterSpecification
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: testerSpec 为空
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: DeviceSpecification * testerSpec：Tester规格存放地址
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetTesterSpecification(int connID, DeviceSpecification *testerSpec);
WTtester_DLL_API int CALL_MODE WT_GetTesterSpecification208C(int connID, Device208CSpecification *testerSpec);

//******************************************************************************
// Name:      WT_GetTesterConnStataus
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
// Path:      WT_GetTesterConnStataus
// Access:    public
// Returns:   WTtester_DLL_API int
//              0:网络无法连接或者参数有误
//              !0:pu8Buf装载的有效数据的长度
// Parameter: char * ipAddr
//              ipAddr:字符串，装载目标设备IP，如"192.168.10.254"
// Parameter: char * buffer
//              buffer:返回操作结果，字符串，由设备生成返回.
// Parameter: int bufferSize
//              bufferSize:buffer的大小
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetTesterConnStataus(char *ipAddr, char *buffer, int bufferSize);

//******************************************************************************
// Name:      WT_OperateTesterWave
// Func:      用于添加信号到仪器或者删除仪器的信号
// Path:      WT_OperateTesterWave
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_GENERAL_ERROR: waveName 为空或者其他错误
//              WT_ERR_CODE_UNKNOW_PARAMETER: 参数配置有误
// Parameter: int connID：连接时获取的ID标识.
// Parameter: char * waveName: 信号文件名（包含路径）
// Parameter: int operateOption：操作选项，查看enum TERSTER_WAVE_OPERATE_OPTION
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_OperateTesterWave(int connID, char *waveName, int operateOption);

//******************************************************************************
// Name:      WT_QueryTesterWave
// Func:      查询仪器是否存在指定的波形文件
// Path:      WT_QueryTesterWave
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_GENERAL_ERROR: waveName 为空或者其他错误
//              WT_ERR_CODE_UNKNOW_PARAMETER: 参数配置有误
// Parameter: int connID：连接时获取的ID标识.
// Parameter: char * waveName: 信号文件名（包含路径）
// Parameter: int * waveExists：存储查询结果的容器地址，
//                                    1：仪器存在指定的波形文件，0：仪器不存在指定的波形文件
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_QueryTesterWave(int connID, char *waveName, int *waveExists);

//******************************************************************************
// Name:      WT_GetTesterAllWaveNames
// Func:      获取仪器中的信号文件列表
// Path:      WT_GetTesterAllWaveNames
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:操作成功
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_GENERAL_ERROR: fileNameBuffer 为空或者其他错误
//              WT_ERR_CODE_UNKNOW_PARAMETER: 参数配置有误
// Parameter: int connID：连接时获取的ID标识.
// Parameter: char * fileNameBuffer: 用于存储仪器信号文件名列表的容器地址，相邻两个信号文件名以"\r\n"隔开.
// Parameter: int fileNameBufferSize: fileNameBuffer的大小，单位：字节.
// Parameter: int * fileCount: 用于存储仪器信号文件数量的容器地址 (注：如果fileNameBuffer太小则不能完整存储仪器中所有的信号文件名).
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetTesterAllWaveNames(int connID, char *fileNameBuffer, int fileNameBufferSize, int *fileCount);

//******************************************************************************
// Name:      WT_BeamformingCalibrationChannelEstDutTX
// Func:      在Calibration时，控制DUT发送，WT-200接收，调用此函数估算出Hab 1x3
// Path:      WT_BeamformingCalibrationChannelEstDutTX
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: int demod
//              枚举量 802.11 分析模式.WT_DEMOD_ENUM
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_BeamformingCalibrationChannelEstDutTX(int connID, int demod);

//******************************************************************************
// Name:      WT_BeamformingCalibrationChannelEstDutRX
// Func:      在Calibration时，控制WT-200发送，DUT接收，调用此函数估算出Hba 3x1
// Path:      WT_BeamformingCalibrationChannelEstDutRX
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: double *dutChannelEst
//              从DUT读取到的通道信息数组
// Parameter: int dutChannelEstLength
//              从DUT读取到的通道信息数组长度
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_BeamformingCalibrationChannelEstDutRX(int connID, double *dutChannelEst, int dutChannelEstLength);

//******************************************************************************
// Name:      WT_BeamformingCalibrationResult
// Func:      在Calibration时，在获取Hab 1x3和Hba 3x1后，通过此函数获取相位
// Path:      WT_BeamformingCalibrationResult
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: double *resultAngle
//              结果相位值, 返回为数组（返回最大长度8元素）, 由调用方提供数组内存
// Parameter: int *resultAngleLength
//              结果相位值数组长度
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_BeamformingCalibrationResult(int connID, double *resultAngle, int *resultAngleLength);

//******************************************************************************
// Name:      WT_BeamformingVerification
// Func:      在Verification时，通过配置DUT进入相应状态并输出Beamforming信号，WT-200接收
//            并解析DUT信号，计算Beamforming带来的增益。
// Path:      WT_BeamformingVerification
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: double *diffPower
//              返回结果，Beamforming增益dB
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_BeamformingVerification(int connID, double *diffPower);


//******************************************************************************
// Name:      WT_BeamformingCalculateChannelProfile
// Func:      在Calibration时，通过此函数获取DUT发送信号的幅度和相位，此函数适用于MTK方案
// Path:      WT_BeamformingCalculateChannelProfile
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: int connID
//              connID: 连接时获取的ID标识.
// Parameter: double *resultBuf
//              结果相位值, 返回为数组（幅度、相位）, 由调用方提供数组内存
// Parameter: int resultAngleLength
//              结果值数组长度，必须是2的倍数
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_BeamformingCalculateChannelProfile(int connID, int demod, double *resultBuf, int resultLength);
//******************************************************************************
// Name:      WT_SetVSAMaxIFG
// Func:      设置VSA max wave gap时间
// Path:      WT_SetVSAMaxIFG
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: maxgap 超出范围
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int maxgap: maxgap超时时间(单位：ms, 范围：1-10000)
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetVSAMaxIFG(int connID, int maxgap);

//******************************************************************************
// Name:      WT_SetVSASampleRateMode
// Func:      设置仪器采样速率
// Path:      WT_SetVSASampleRateMode
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_GENERAL_ERROR: 配置VsaSampleRate失败，仪器不支持该功能
//              WT_ERR_CODE_UNKNOW_PARAMETER: smpFreqMode的值不在支持的枚举中
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int sampleRateMode：支持的采样速率(enum TESTER_SAMPLERATE_MODE)
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetVSASampleRateMode(int connID, int sampleRateMode);

//******************************************************************************
// Name:      WT_SetBandwidthMode
// Func:      设置带宽识别模式
// Path:      WT_SetBandwidthMode
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER：参数有误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int bandwidthDetect: 带宽模式, 参考 WT_BANDWIDTH_DETECT_ENUM 枚举
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetBandwidthMode(int connID, int bandwidthDetect);

//******************************************************************************
// Name:      WT_SetZigBeeAnalysisOptimise
// Func:      ZigBee分析优化选项
// Path:      WT_SetZigBeeAnalysisOptimise
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
WTtester_DLL_API int CALL_MODE WT_SetZigBeeAnalysisOptimise(int connID, int AnalysisOptimise);

//******************************************************************************
// Name:      WT_GetSymbolsEvm
// Func:      获取某段Symbol范围内的Evm均值
// Path:      WT_GetSymbolsEvm
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER：参数有误
//              WT_ERR_CODE_GENERAL_ERROR：获取结果失败
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int startSymbol: 起始Symbol序号，从0开始.
// Parameter: int endSymbol: 结束Symbol序号，计算时不包含该Symbol.
// Parameter: int evmResultType: 设定取哪种类型的evm结果，参照enum SYMBOLS_EVM_RESULT_TYPE.
// Parameter: double * evmResult(Out): 存储规定Symbol范围内的Evm均值的缓存，单位dB.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetSymbolsEvm(int connID, int startSymbol, int endSymbol, int evmResultType, double *evmResult);

//******************************************************************************
// Name:      WT_DataStore
// Func:      保存Vsa信号数据
// Path:      WT_DataStore
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_GENERAL_ERROR: 保存失败
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char * fileName: 保存文件名（包含路径）
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_DataStore(int connID, char *fileName);

//************************************
// Method:    WT_SetSpectrumMaskErrorAnalyzeRange
// Func:      设置频谱模板错误率分析的范围，默认全频段分析，
//            比如要分析中间40M带宽范围的频谱错误率，startFrequency设为-20，endFrequency设为20
// Path:      WT_SetSpectrumMaskErrorAnalyzeRange
// Access:    public 
// Returns:   WTtester_DLL_API int
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int startFrequency：分析的起始频率值
// Parameter: int endFrequency：分析的结束频率值
//************************************
WTtester_DLL_API int CALL_MODE WT_SetSpectrumMaskErrorAnalyzeRange(int connID, int startFrequency, int endFrequency);

#ifdef _WIN32
//************************************
// Method:    WT_SetCrashDumpIf
// Func:      设置是否开启程序崩溃抓取并保存崩溃信息的功能
// Path:      WT_SetCrashDumpIf
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_GENERAL_ERROR: 操作失败
// Parameter: int crashDumpMode：程序崩溃信息是否抓取, 0: 崩溃不抓取信息, 1: 崩溃抓取信息
//************************************
WTtester_DLL_API int CALL_MODE WT_SetCrashDumpIf(int crashDumpMode);
#endif

//************************************
// Method:    WT_SetSpectrumMaskVersion
// Func:      设置频谱模板版本，只适用于11n
// Path:      WT_SetSpectrumMaskVersion
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: version为参数错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int version：频谱模板版本，对应枚举SPECTRUM_MASK_VERSION
//************************************
WTtester_DLL_API int CALL_MODE WT_SetSpectrumMaskVersion(int connID, int version);

//************************************
// Method:    WT_SetAnalyzeFrameIndex
// Func:      设置分析第几帧信号
// Path:      WT_SetAnalyzeFrameIndex
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: version为参数错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int analyzeFrameIndex：第几帧信号，从0开始
//************************************
WTtester_DLL_API int CALL_MODE WT_SetAnalyzeFrameIndex(int connID, int analyzeFrameIndex);

//************************************
// Method:    WT_SetZWaveRate
// Func:      设置ZWave速率
// Path:      WT_SetZWaveRate
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: zWaveRate参数错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int zWaveRate：ZWave Rate，对应枚举ZWAVE_RATE_ENUM
//************************************
WTtester_DLL_API int CALL_MODE WT_SetZWaveRate(int connID, int zWaveRate);

//************************************
// Method:    WT_ExecInternalCmd
// Func:      执行内部命令
// Path:      WT_ExecInternalCmd
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: zWaveRate参数错误
// Parameter: char *ipAddr: 字符串，装载目标设备IP，如"192.168.10.254"
// Parameter: char *cmd: 需要执行的命令.
// Parameter: int cmdLen：命令长度.
// Parameter: char *buffer: 结果缓存.
// Parameter: char *bufferSize: 缓存大小.
//************************************
WTtester_DLL_API int CALL_MODE WT_ExecInternalCmd(char *ipAddr, char *cmd, int cmdLen, char *buffer, int bufferSize);

//************************************
// Method:    WT_SetLrwpanFskAnalyzeParam
// Func:      设置LrwpanFsk分析参数
// Path:      WT_SetLrwpanFskAnalyzeParam
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: pLrwpanFskParam参数错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: LrwpanFskParam *pLrwpanFskParam：LrwpanFsk分析参数
//************************************
WTtester_DLL_API int CALL_MODE WT_SetLrwpanFskAnalyzeParam(int connID, LrwpanFskParam *pLrwpanFskParam);

//************************************
// Method:    WT_AuthenGet
// Func:      获取认证字符，只对WT208H生效
// Path:      WT_AuthenGet
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER：参数有误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char *buffer：保存认证字符的缓存
// Parameter: int bufferSize：缓存大小
//************************************
WTtester_DLL_API int CALL_MODE WT_AuthenGet(int connID, char *buffer, int bufferSize);

//************************************
// Method:    WT_AuthenSet
// Func:      下发加密后的字符，只对WT208H生效
// Path:      WT_AuthenSet
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确，认证通过
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER：参数有误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: char *buffer：保存加密字符的缓存
// Parameter: int dataLen：加密字符长度
//************************************
WTtester_DLL_API int CALL_MODE WT_AuthenSet(int connID, char *buffer, int dataLen);

//************************************
// Method:    WT_SetLargePowerIFGSwitch
// Func:      设置大功率IFG优化开关
// Path:      WT_SetLargePowerIFGSwitch
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: 操作完全正确
//              WT_ERR_CODE_CONNECT_FAIL:连接未建立或已中断
//              WT_ERR_CODE_UNKNOW_PARAMETER: zWaveRate参数错误
// Parameter: int connID: 连接时获取的ID标识.
// Parameter: int swState：开关状态，0-关闭，1-打开
//************************************
WTtester_DLL_API int CALL_MODE WT_SetLargePowerIFGSwitch(int connID, int swState);

#endif


