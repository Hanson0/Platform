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
	double  freq;               //VSA�ز�Ƶ��,��λ��Hz
	double  max_power;          //����������,dBm; (�����ʵ������������Ĺ��ʻ������ټ�12dB��������չ��ʷ�Χδ֪����������Auto Range)
	double  smp_time;           //����ʱ��,us
	int     rfPort;             //ָ��VSAʹ�õ�RF�˿�

	int     trig_type;          //����ģʽ,WT_TRIG_TYPE_ENUM
	double  trig_level;         //������ƽ,��max_power�Ĳ��,dB
	double  trig_timeout;       //�����ȴ���ʱ,sec����ʱ����TimeoutWaiting��ʱ���໥������
	double  trig_pretime;       //��������ʱ��,��������ǰ����ʱ���ڵ�����,us

	int     demod;              //802.11 ����ģʽ.WT_DEMOD_ENUM
	int     iq_swap;            //IQ����(Ƶ�׷�ת). WT_IQ_SWAP_ENUM

	int     ph_corr;            //802.11 a/g/n/ac ��λ����. WT_PH_CORR_ENUM
	int     ch_estimate;        //802.11 a/g/n/ac ͨ������. WT_CH_EST_ENUM
	int     sym_tim_corr;       //802.11 a/g/n/ac ʱ�����. WT_SYM_TIM_ENUM
	int     freq_sync;          //802.11 a/g/n/ac Ƶ��ͬ��. WT_FREQ_SYNC_ENUM
	int     ampl_track;         //802.11 a/g/n/ac ���ȸ���. WT_AMPL_TRACK_ENUM

	int     evm_method_11b;     //802.11 b EVM��ʽ.  WT_11B_METHOD_ENUM
	int     dc_removal;         //802.11 b ֱ��ȥ��. WT_DC_REMOVAL_ENUM
	int     eq_taps;            //802.11 b ��������. WT_EQ_ENUM
	int     cck_ph_corr;        //802.11 b ��λ����. WT_PH_CORR_11b_ENUM

	int     bt_Rate;            //Bluetooth����, WT_BT_DATARATE
	int     bt_packet_type;     //Bluetooth������, WT_BT_PACKETTYPE(Ĭ������ΪWT_BT_PACKETTYPE_NULL����)

	int     TimeoutWaiting;     //�ڶ���������£��ȴ������ʱ�䣬Ĭ��ֵΪ8�룬��λsec

} VsaParameter;

typedef struct
{
	double  freq;               //VSG�ز�Ƶ��,��λ��Hz
	double  power;              //VSG����,dBm
	int     rfPort;             //ָ��VSGʹ�õ�RF�˿�

	int     waveType;           //Wave���ͣ�WT_SIGNAL_ENUM. SIG_USERFILE: ��ȡ����wave�ļ�; SIG_TESTERFILE: ʹ�������洢��wave�ļ�(WT-208�̼��汾���ڻ����3.0.1.10�Ĳ�֧�ָ���); (����ѡ���SIG_USERFILE��SIG_TESTERFILE�����ѡ�����WT-208����֧��)
	char    *wave;              //VSG�����ļ�,���Ϊnull,ֻ�����豸���ã�������wave�ļ���������repeat��wave_gap
	int     repeat;             //ѭ�����ʹ���
	double  wave_gap;           //���η��ͼ����us

	int     TimeoutWaiting;     //�ڶ���������£��ȴ������ʱ�䣬Ĭ��ֵΪ8�룬��λsec
} VsgParameter;

//******************************************************************************
// Name:      WT_InitMaxCaptureTime
// Func:      ��ʼ��120MHz��������֧�ֵ�������ʱ��.
//            ע��: �ýӿ�Ϊ��ѡ���ã�������ã������ڸ��ĵ�������API֮ǰ����,
//            �Ҵ˺���ֻ�ܵ���һ��.
//            ���û�е��øýӿ�,��Ĭ��֧�ֵĲ���ʱ��Ϊ10000us.
// Path:      WT_InitMaxCaptureTime
// Access:    public
// Returns:   WTtester_DLL_API void
// Parameter: int maxCaptureTimeUs:  ������ʱ��,��λ: us(΢��)
//******************************************************************************
WTtester_DLL_API void CALL_MODE WT_InitMaxCaptureTime(int maxCaptureTimeUs);

//******************************************************************************
// Name:      WT_DLLInitialize
// Func:      ��ʼ��WTtester API����ע��: �ڵ��ø��ĵ�������API֮ǰ����øýӿ�,
//            �Ҵ˺���ֻ�ܵ���һ��.
// Path:      WT_DLLInitialize
// Access:    public
// Returns:   WTtester_DLL_API void
// Parameter: void
//******************************************************************************
WTtester_DLL_API void CALL_MODE WT_DLLInitialize(void);

//******************************************************************************
// Name:      WT_DLLTerminate
// Func:      �ͷ�WTtester API����
//            ע��ǿ�ҽ��������в�������֮��ŵ��øýӿڣ����������������ڴ洦�����,
//            �Ҵ˺���ֻ�ܵ���һ��.
// Path:      WT_DLLTerminate
// Access:    public
// Returns:   WTtester_DLL_API void
// Parameter: void
//******************************************************************************
WTtester_DLL_API void CALL_MODE WT_DLLTerminate(void);

//******************************************************************************
// Name:      WT_Connect
// Func:      ����ָ��������(WTtester)
//            �ýӿڲ���ǿ������ָ��������������EXE֮�������
//            ����WT-208ʱ�����ͬʱ����4�����ӣ���������ǽ�֧��1������
//            �����κ�����ʱ�����ָ�������Ѿ���WLAN Meter���ӣ���ýӿ��޷������µ�����
//            ����ʧ��ʱ������ͨ��WT_GetTesterConnStataus��ѯʧ��ԭ��
// Path:      WT_Connect
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: char * ipAddr
//              ipAddr:������IP��ַ������"192.168.10.254"
// Parameter: int * connID
//              connID: ����ID��ʶ, ���ں���Դ����Ӳ���ʶ��.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_Connect(char *ipAddr, int *connID);

//******************************************************************************
// Name:      WT_ForceConnect
// Func:      ǿ�����ӵ�������
// Path:      WT_ForceConnect
// Access:    public
// Returns:   WTtester_DLL_API int
//             WT_ERR_CODE_OK
//             WT_ERR_CODE_CONNECT_FAIL
// Parameter: char * ipAddr:������IP��ַ������"192.168.10.254"
// Parameter: int * connID: ����ID��ʶ, ���ں���Դ����Ӳ���ʶ��.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_ForceConnect(char *ipAddr, int *connID);

//******************************************************************************
// Name:      WT_DisConnect
// Func:      �Ͽ����ӣ��ͷŸ�������ռ�õ�������Դ
// Path:      WT_DisConnect
// Access:    public
// Returns:   WTtester_DLL_API void
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WTtester_DLL_API void CALL_MODE WT_DisConnect(int connID);

//******************************************************************************
// Name:      WT_GetDefaultParameter
// Func:      ����Ĭ�ϵ�VSA������vsaParam,  VSG������vsgParam��
//            ����������VSA,VSG֮ǰ��ִ�иò�����֮�����ڴ˻����Ͻ����޸�
// Path:      WT_GetDefaultParameter
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: VsaParameter * vsaParam
//              VSA��ϸ����
// Parameter: VsgParameter * vsgParam
//              VSG��ϸ����(repeat�Լ�wave_gap���ֲ������).
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetDefaultParameter(VsaParameter *vsaParam, VsgParameter *vsgParam);

//******************************************************************************
// Name:      WT_SetExternalGain
// Func:      ����(DUT��WTtester���)�ⲿ���棬ͬʱ��VSA�Լ�VSG��Ч
// Path:      WT_SetExternalGain
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: double extGain
//              extGain: �ⲿ����ֵ����λdB��
//              ע��:�˴�Ϊ�ⲿ���棬�����ⲿ˥����
//              ǿ�ҽ���ʹ��ʵ������ֵ����ֵ���ù�����ܻᵼ��VSA��VSG����쳣.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetExternalGain(int connID, double extGain);

//******************************************************************************
// Name:      WT_GetExternalGain
// Func:      ��ȡ(DUT��WTtester���)�ⲿ���棬����ʱʹ��
// Path:      WT_GetExternalGain
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: CableVerifyParameter * param
//              param:  ���߲���
// Parameter: double * extGain
//              extGain: �ⲿ����ֵ����λdB��
//              ע��:�˴�Ϊ�ⲿ���棬�����ⲿ˥������ʹ�øýӿ�֮��
//              ���軹ԭ�������Ĳ��ԣ�������WT_SetVSA/WT_SetVSG
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetExternalGain(int connID, CableVerifyParameter *param, double *extGain);

//******************************************************************************
// Name:      WT_SetVSA
// Func:      ����VSA����
// Path:      WT_SetVSA
// Access:    public
// Returns:   WTtester_DLL_API int
//WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: VsaParameter * vsaParam
//              vsaParam: VSA��ϸ����
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetVSA(int connID, VsaParameter *vsaParam);

//******************************************************************************
// Name:      WT_SetVSG
// Func:      ����VSG������
//              ע�⣺���øò���֮�����ָ���Ĳ����ļ���Ч����ֹͣVSG,����Ҫ�Ļ������¿���
//              ���ָ���Ĳ����ļ���Ч���߲���vsgParamΪ�գ��᷵��WT_ERR_CODE_UNKNOW_PARAMETER���Ҳ�Ӱ��֮ǰ��VSG״̬
// Path:      WT_SetVSG
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: VsgParameter * vsgParam
//              vsgParam: VSG��ϸ����
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetVSG(int connID, VsgParameter *vsgParam);

//******************************************************************************
// Name:      WT_SetVSA_AutoRange
// Func:      ����VSA�������Զ�ƥ��ο���ƽֵ(Max Power Level),����ƥ��ɹ�֮�����õ�WTtester��ȥ
//              ǿ�ҽ����������ź�δ֪��ǰ���£�����ʹ�øýӿ�
//
//              ������뵽�������źż��(IFG)����200ms�������źŹ�������ǳ���ʱ�����ܻᵼ��Auto Range���صĲο���ƽ��׼ȷ
// Path:      WT_SetVSA_AutoRange
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: VsaParameter * vsaParam
//              vsaParam: VSA��ϸ�����������óɹ�֮�󣬻᷵���µĲο���ƽֵ
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetVSA_AutoRange(int connID, VsaParameter *vsaParam);

//******************************************************************************
// Name:      WT_DataCapture
// Func:      ����ָ����VSA������������ץȡ
// Path:      WT_DataCapture
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_DataCapture(int connID);

//******************************************************************************
// Name:      WT_StopDataCapture
// Func:      ֹͣ�ɼ�����
// Path:      WT_StopDataCapture
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connId: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_StopDataCapture(int connID);

//******************************************************************************
// Name:      WT_GetResult
// Func:      ��ȡָ��parameter�ķ����������ȡ�ɹ��󣬸��������ֵ����Ч.
//              ע��:�ò����ǰ��Ϊ�Ѿ�ץȡ�����������(���ȵ��ýӿ�DataCapture)
// Path:      WT_GetResult
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_NO_DATA_CAPTURED:δץȡ����
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char * anaParmString
//              �������(�ַ�������)������WT_RES_EVM_ALL
// Parameter: double * result
//              result: ��Ӧ���ֵ
// Parameter: char * description
//              description: �ý��ֵ�Ķ�Ӧ����
// Parameter: char * unit
//              unit: �ý��ֵ�Ķ�Ӧ�ĵ�λ
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetResult(int connID, char *anaParmString, double *result, char *description, char *unit);

//******************************************************************************
// Name:      WT_GetVectorResultElementSize
// Func:      ��ȡ�����ÿ����Ԫ���ݵĴ�С����λ���ֽ�
// Path:      WT_GetVectorResultElementSize
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_NO_DATA_CAPTURED:δץȡ����
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char * anaParmString���������(�ַ�������)������WT_RES_EVM_ALL
// Parameter: int * elementSize�������Ԫ���ݵĴ�С
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetVectorResultElementSize(int connID, char *anaParmString, int *elementSize);

//******************************************************************************
// Name:      WT_GetVectorResultElementCount
// Func:      ��ȡ��������ĳ���
// Path:      WT_GetVectorResultElementCount
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_NO_DATA_CAPTURED:δץȡ����
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char * anaParmString���������(�ַ�������)������WT_RES_EVM_ALL
// Parameter: int * elementCount���������ĳ���
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetVectorResultElementCount(int connID, char *anaParmString, int *elementCount);

//******************************************************************************
// Name:      WT_GetVectorResult
// Func:      ��ȡָ��parameter�ķ����������ȡ�ɹ��󣬸��������ֵ����Ч.
//              ע��:�ò����ǰ��Ϊ�Ѿ�ץȡ�����������(���ȵ��ýӿ�DataCapture)���ý�������������ʽ����
// Path:      WT_GetVectorResult
// Access:    public
// Returns:   WTtester_DLL_API int: ����ʵ�ʸ��Ƶ��������Ŀ����Ԫ��С�������resultTypeΪ׼������0�������������߷���ʧ��
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char * anaParmString���������(�ַ�������)������enum WT_RES_EVM_ALL
// Parameter: void * result: ��Ӧ����洢����
// Parameter: int resultType��������������ͣ��ο�WT_RESULT_DATA_TYPE
// Parameter: int resultSize������洢�����С����λ���ֽ�
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetVectorResult(int connID, char *anaParmString, void *result, int resultType, int resultSize);

//******************************************************************************
// Name:      WT_StartVSG
// Func:      ����ָ����VSG���������ź�(wave)���ͣ����ڷ�����ɺ�ŷ���(ͬ������)
// Path:      WT_StartVSG
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_VsgInaccuracy:VSG���ʲ�׼ȷ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_StartVSG(int connID);

//******************************************************************************
// Name:      WT_AsynStartVSG
// Func:      ����ָ����VSG���������ź�(wave)���ͣ����������·���ֱ�ӷ���(�첽����)
// Path:      WT_AsynStartVSG
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_VsgInaccuracy:���͹��ʲ�׼ȷ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_AsynStartVSG(int connID);

//******************************************************************************
// Name:      WT_GetVSGCurrentState
// Func:      ��ȡVSG��ǰ״̬.
// Path:      WT_GetVSGCurrentState
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int * state
//              state: VSG״̬����ָ��.VSG״̬���:enum WT_VSG_STATE
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetVSGCurrentState(int connID, int *state);

//******************************************************************************
// Name:      WT_StopVSG
// Func:      ֹͣVSG.
// Path:      WT_StopVSG
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_StopVSG(int connID);

//******************************************************************************
// Name:      WT_SetWT208NetInfo
// Func:      ����WT208�ļ���������ʹ����Ϣ.
// Path:      WT_SetWT208NetInfo
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: WT_208_NET_TYPE * ipAddrs
//              ipAddrs: �����ڵ�������Ϣ
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetWT208NetInfo(int connID, WT_208_NET_TYPE *ipAddrs);
WTtester_DLL_API int CALL_MODE WT_SetVirtualSubNetInfo(int connID, WT_VIRTUAL_NET_TYPE *ipAddrs);
//******************************************************************************
// Name:      WT_GetTesterVersion
// Func:      ��ȡ�����ǵİ汾�Լ�����������.
// Path:      WT_GetTesterVersion
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER:u32BufSize��С���������߻�δ����ָ���Ĳ�����
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: TesterInfo * buffer
//              buffer:װ�ذ汾��Ϣ������,װ�ؽ�����TesterInfo
// Parameter: int bufferSize
//              bufferSize: ָ�������Ĵ�С
// Parameter: int * testerType
//              testerType����������,���WT_TESTER_TYPE
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetTesterVersion(int connID, TesterInfo *buffer, int bufferSize, int *testerType);

//******************************************************************************
// Name:      WT_GetTesterSpecification
// Func:      ��ȡ�������
// Path:      WT_GetTesterSpecification
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: testerSpec Ϊ��
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: DeviceSpecification * testerSpec��Tester����ŵ�ַ
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetTesterSpecification(int connID, DeviceSpecification *testerSpec);
WTtester_DLL_API int CALL_MODE WT_GetTesterSpecification208C(int connID, Device208CSpecification *testerSpec);

//******************************************************************************
// Name:      WT_GetTesterConnStataus
// Func:      ���ڲ鿴��������״̬.
//              ע�⣺
//              �����̫��ʹ�ã��豸��������3��״̬:
//              case 1:
//              BUSY:IP:192.168.10.2;PORT:28691;
//                  ��ʾ�豸����192.168.10.2��28691�˿�ʹ��
//              case 2:
//              ERR:DEVICE DOES NOT EXIST
//                      �޷�����ipAddrָ�����豸
//              case 3:
//              IDLE:
//                  �豸���ڿ���״̬
// Path:      WT_GetTesterConnStataus
// Access:    public
// Returns:   WTtester_DLL_API int
//              0:�����޷����ӻ��߲�������
//              !0:pu8Bufװ�ص���Ч���ݵĳ���
// Parameter: char * ipAddr
//              ipAddr:�ַ�����װ��Ŀ���豸IP����"192.168.10.254"
// Parameter: char * buffer
//              buffer:���ز���������ַ��������豸���ɷ���.
// Parameter: int bufferSize
//              bufferSize:buffer�Ĵ�С
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetTesterConnStataus(char *ipAddr, char *buffer, int bufferSize);

//******************************************************************************
// Name:      WT_OperateTesterWave
// Func:      ��������źŵ���������ɾ���������ź�
// Path:      WT_OperateTesterWave
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_GENERAL_ERROR: waveName Ϊ�ջ�����������
//              WT_ERR_CODE_UNKNOW_PARAMETER: ������������
// Parameter: int connID������ʱ��ȡ��ID��ʶ.
// Parameter: char * waveName: �ź��ļ���������·����
// Parameter: int operateOption������ѡ��鿴enum TERSTER_WAVE_OPERATE_OPTION
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_OperateTesterWave(int connID, char *waveName, int operateOption);

//******************************************************************************
// Name:      WT_QueryTesterWave
// Func:      ��ѯ�����Ƿ����ָ���Ĳ����ļ�
// Path:      WT_QueryTesterWave
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_GENERAL_ERROR: waveName Ϊ�ջ�����������
//              WT_ERR_CODE_UNKNOW_PARAMETER: ������������
// Parameter: int connID������ʱ��ȡ��ID��ʶ.
// Parameter: char * waveName: �ź��ļ���������·����
// Parameter: int * waveExists���洢��ѯ�����������ַ��
//                                    1����������ָ���Ĳ����ļ���0������������ָ���Ĳ����ļ�
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_QueryTesterWave(int connID, char *waveName, int *waveExists);

//******************************************************************************
// Name:      WT_GetTesterAllWaveNames
// Func:      ��ȡ�����е��ź��ļ��б�
// Path:      WT_GetTesterAllWaveNames
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_GENERAL_ERROR: fileNameBuffer Ϊ�ջ�����������
//              WT_ERR_CODE_UNKNOW_PARAMETER: ������������
// Parameter: int connID������ʱ��ȡ��ID��ʶ.
// Parameter: char * fileNameBuffer: ���ڴ洢�����ź��ļ����б��������ַ�����������ź��ļ�����"\r\n"����.
// Parameter: int fileNameBufferSize: fileNameBuffer�Ĵ�С����λ���ֽ�.
// Parameter: int * fileCount: ���ڴ洢�����ź��ļ�������������ַ (ע�����fileNameBuffer̫С���������洢���������е��ź��ļ���).
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetTesterAllWaveNames(int connID, char *fileNameBuffer, int fileNameBufferSize, int *fileCount);

//******************************************************************************
// Name:      WT_BeamformingCalibrationChannelEstDutTX
// Func:      ��Calibrationʱ������DUT���ͣ�WT-200���գ����ô˺��������Hab 1x3
// Path:      WT_BeamformingCalibrationChannelEstDutTX
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int demod
//              ö���� 802.11 ����ģʽ.WT_DEMOD_ENUM
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_BeamformingCalibrationChannelEstDutTX(int connID, int demod);

//******************************************************************************
// Name:      WT_BeamformingCalibrationChannelEstDutRX
// Func:      ��Calibrationʱ������WT-200���ͣ�DUT���գ����ô˺��������Hba 3x1
// Path:      WT_BeamformingCalibrationChannelEstDutRX
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: double *dutChannelEst
//              ��DUT��ȡ����ͨ����Ϣ����
// Parameter: int dutChannelEstLength
//              ��DUT��ȡ����ͨ����Ϣ���鳤��
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_BeamformingCalibrationChannelEstDutRX(int connID, double *dutChannelEst, int dutChannelEstLength);

//******************************************************************************
// Name:      WT_BeamformingCalibrationResult
// Func:      ��Calibrationʱ���ڻ�ȡHab 1x3��Hba 3x1��ͨ���˺�����ȡ��λ
// Path:      WT_BeamformingCalibrationResult
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: double *resultAngle
//              �����λֵ, ����Ϊ���飨������󳤶�8Ԫ�أ�, �ɵ��÷��ṩ�����ڴ�
// Parameter: int *resultAngleLength
//              �����λֵ���鳤��
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_BeamformingCalibrationResult(int connID, double *resultAngle, int *resultAngleLength);

//******************************************************************************
// Name:      WT_BeamformingVerification
// Func:      ��Verificationʱ��ͨ������DUT������Ӧ״̬�����Beamforming�źţ�WT-200����
//            ������DUT�źţ�����Beamforming���������档
// Path:      WT_BeamformingVerification
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: double *diffPower
//              ���ؽ����Beamforming����dB
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_BeamformingVerification(int connID, double *diffPower);


//******************************************************************************
// Name:      WT_BeamformingCalculateChannelProfile
// Func:      ��Calibrationʱ��ͨ���˺�����ȡDUT�����źŵķ��Ⱥ���λ���˺���������MTK����
// Path:      WT_BeamformingCalculateChannelProfile
// Access:    public
// Returns:   WTtester_DLL_API int
// Parameter: int connID
//              connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: double *resultBuf
//              �����λֵ, ����Ϊ���飨���ȡ���λ��, �ɵ��÷��ṩ�����ڴ�
// Parameter: int resultAngleLength
//              ���ֵ���鳤�ȣ�������2�ı���
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_BeamformingCalculateChannelProfile(int connID, int demod, double *resultBuf, int resultLength);
//******************************************************************************
// Name:      WT_SetVSAMaxIFG
// Func:      ����VSA max wave gapʱ��
// Path:      WT_SetVSAMaxIFG
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: maxgap ������Χ
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int maxgap: maxgap��ʱʱ��(��λ��ms, ��Χ��1-10000)
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetVSAMaxIFG(int connID, int maxgap);

//******************************************************************************
// Name:      WT_SetVSASampleRateMode
// Func:      ����������������
// Path:      WT_SetVSASampleRateMode
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_GENERAL_ERROR: ����VsaSampleRateʧ�ܣ�������֧�ָù���
//              WT_ERR_CODE_UNKNOW_PARAMETER: smpFreqMode��ֵ����֧�ֵ�ö����
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int sampleRateMode��֧�ֵĲ�������(enum TESTER_SAMPLERATE_MODE)
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetVSASampleRateMode(int connID, int sampleRateMode);

//******************************************************************************
// Name:      WT_SetBandwidthMode
// Func:      ���ô���ʶ��ģʽ
// Path:      WT_SetBandwidthMode
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER����������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int bandwidthDetect: ����ģʽ, �ο� WT_BANDWIDTH_DETECT_ENUM ö��
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetBandwidthMode(int connID, int bandwidthDetect);

//******************************************************************************
// Name:      WT_SetZigBeeAnalysisOptimise
// Func:      ZigBee�����Ż�ѡ��
// Path:      WT_SetZigBeeAnalysisOptimise
// Access:    public
// Returns:   int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER����������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int AnalysisOptimise: �����Ż�����, �ο� WT_ZB_ANALYSIS_OPTIMISE_ENUM ö��
//              WT_ZB_ANALYSIS_OPTIMISE_DISABLED == 0;
//              WT_ZB_ANALYSIS_OPTIMISE_ENABLED  == 1;
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_SetZigBeeAnalysisOptimise(int connID, int AnalysisOptimise);

//******************************************************************************
// Name:      WT_GetSymbolsEvm
// Func:      ��ȡĳ��Symbol��Χ�ڵ�Evm��ֵ
// Path:      WT_GetSymbolsEvm
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER����������
//              WT_ERR_CODE_GENERAL_ERROR����ȡ���ʧ��
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int startSymbol: ��ʼSymbol��ţ���0��ʼ.
// Parameter: int endSymbol: ����Symbol��ţ�����ʱ��������Symbol.
// Parameter: int evmResultType: �趨ȡ�������͵�evm���������enum SYMBOLS_EVM_RESULT_TYPE.
// Parameter: double * evmResult(Out): �洢�涨Symbol��Χ�ڵ�Evm��ֵ�Ļ��棬��λdB.
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_GetSymbolsEvm(int connID, int startSymbol, int endSymbol, int evmResultType, double *evmResult);

//******************************************************************************
// Name:      WT_DataStore
// Func:      ����Vsa�ź�����
// Path:      WT_DataStore
// Access:    public
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_GENERAL_ERROR: ����ʧ��
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char * fileName: �����ļ���������·����
//******************************************************************************
WTtester_DLL_API int CALL_MODE WT_DataStore(int connID, char *fileName);

//************************************
// Method:    WT_SetSpectrumMaskErrorAnalyzeRange
// Func:      ����Ƶ��ģ������ʷ����ķ�Χ��Ĭ��ȫƵ�η�����
//            ����Ҫ�����м�40M����Χ��Ƶ�״����ʣ�startFrequency��Ϊ-20��endFrequency��Ϊ20
// Path:      WT_SetSpectrumMaskErrorAnalyzeRange
// Access:    public 
// Returns:   WTtester_DLL_API int
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int startFrequency����������ʼƵ��ֵ
// Parameter: int endFrequency�������Ľ���Ƶ��ֵ
//************************************
WTtester_DLL_API int CALL_MODE WT_SetSpectrumMaskErrorAnalyzeRange(int connID, int startFrequency, int endFrequency);

#ifdef _WIN32
//************************************
// Method:    WT_SetCrashDumpIf
// Func:      �����Ƿ����������ץȡ�����������Ϣ�Ĺ���
// Path:      WT_SetCrashDumpIf
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_GENERAL_ERROR: ����ʧ��
// Parameter: int crashDumpMode�����������Ϣ�Ƿ�ץȡ, 0: ������ץȡ��Ϣ, 1: ����ץȡ��Ϣ
//************************************
WTtester_DLL_API int CALL_MODE WT_SetCrashDumpIf(int crashDumpMode);
#endif

//************************************
// Method:    WT_SetSpectrumMaskVersion
// Func:      ����Ƶ��ģ��汾��ֻ������11n
// Path:      WT_SetSpectrumMaskVersion
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: versionΪ��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int version��Ƶ��ģ��汾����Ӧö��SPECTRUM_MASK_VERSION
//************************************
WTtester_DLL_API int CALL_MODE WT_SetSpectrumMaskVersion(int connID, int version);

//************************************
// Method:    WT_SetAnalyzeFrameIndex
// Func:      ���÷����ڼ�֡�ź�
// Path:      WT_SetAnalyzeFrameIndex
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: versionΪ��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int analyzeFrameIndex���ڼ�֡�źţ���0��ʼ
//************************************
WTtester_DLL_API int CALL_MODE WT_SetAnalyzeFrameIndex(int connID, int analyzeFrameIndex);

//************************************
// Method:    WT_SetZWaveRate
// Func:      ����ZWave����
// Path:      WT_SetZWaveRate
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: zWaveRate��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int zWaveRate��ZWave Rate����Ӧö��ZWAVE_RATE_ENUM
//************************************
WTtester_DLL_API int CALL_MODE WT_SetZWaveRate(int connID, int zWaveRate);

//************************************
// Method:    WT_ExecInternalCmd
// Func:      ִ���ڲ�����
// Path:      WT_ExecInternalCmd
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: zWaveRate��������
// Parameter: char *ipAddr: �ַ�����װ��Ŀ���豸IP����"192.168.10.254"
// Parameter: char *cmd: ��Ҫִ�е�����.
// Parameter: int cmdLen�������.
// Parameter: char *buffer: �������.
// Parameter: char *bufferSize: �����С.
//************************************
WTtester_DLL_API int CALL_MODE WT_ExecInternalCmd(char *ipAddr, char *cmd, int cmdLen, char *buffer, int bufferSize);

//************************************
// Method:    WT_SetLrwpanFskAnalyzeParam
// Func:      ����LrwpanFsk��������
// Path:      WT_SetLrwpanFskAnalyzeParam
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: pLrwpanFskParam��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: LrwpanFskParam *pLrwpanFskParam��LrwpanFsk��������
//************************************
WTtester_DLL_API int CALL_MODE WT_SetLrwpanFskAnalyzeParam(int connID, LrwpanFskParam *pLrwpanFskParam);

//************************************
// Method:    WT_AuthenGet
// Func:      ��ȡ��֤�ַ���ֻ��WT208H��Ч
// Path:      WT_AuthenGet
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER����������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char *buffer��������֤�ַ��Ļ���
// Parameter: int bufferSize�������С
//************************************
WTtester_DLL_API int CALL_MODE WT_AuthenGet(int connID, char *buffer, int bufferSize);

//************************************
// Method:    WT_AuthenSet
// Func:      �·����ܺ���ַ���ֻ��WT208H��Ч
// Path:      WT_AuthenSet
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ����֤ͨ��
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER����������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char *buffer����������ַ��Ļ���
// Parameter: int dataLen�������ַ�����
//************************************
WTtester_DLL_API int CALL_MODE WT_AuthenSet(int connID, char *buffer, int dataLen);

//************************************
// Method:    WT_SetLargePowerIFGSwitch
// Func:      ���ô���IFG�Ż�����
// Path:      WT_SetLargePowerIFGSwitch
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: zWaveRate��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int swState������״̬��0-�رգ�1-��
//************************************
WTtester_DLL_API int CALL_MODE WT_SetLargePowerIFGSwitch(int connID, int swState);

#endif


