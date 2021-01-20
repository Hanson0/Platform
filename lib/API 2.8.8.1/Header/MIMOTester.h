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
	double  freq;                           //VSA�ز�Ƶ��,��λ��Hz
	double  max_power[MAX_TESTER_COUNT];    //����������,dBm; (�����ʵ������������Ĺ��ʻ������ټ�12dB��������չ��ʷ�Χδ֪����������Auto Range)
	double  smp_time;                       //����ʱ��,us
	int     rfPort[MAX_TESTER_COUNT];       //ָ��VSAʹ�õ�RF�˿�

	int     trig_type;                      //����ģʽ,WT_TRIG_TYPE_ENUM
	double  trig_level;                     //������ƽ,��max_power�Ĳ��,dB
	double  trig_timeout;                   //�����ȴ���ʱ,sec����ʱ����TimeoutWaiting��ʱ���໥������
	double  trig_pretime;                   //��������ʱ��,��������ǰ����ʱ���ڵ�����,us

	int     demod;                          //802.11 ����ģʽ.WT_DEMOD_ENUM
	int     iq_swap;                        //IQ����(Ƶ�׷�ת). WT_IQ_SWAP_ENUM

	int     ph_corr;                        //802.11 a/g/n/ac ��λ����. WT_PH_CORR_ENUM
	int     ch_estimate;                    //802.11 a/g/n/ac ͨ������. WT_CH_EST_ENUM
	int     sym_tim_corr;                   //802.11 a/g/n/ac ʱ�����. WT_SYM_TIM_ENUM
	int     freq_sync;                      //802.11 a/g/n/ac Ƶ��ͬ��. WT_FREQ_SYNC_ENUM
	int     ampl_track;                     //802.11 a/g/n/ac ���ȸ���. WT_AMPL_TRACK_ENUM

	int     evm_method_11b;                 //802.11 b EVM��ʽ.  WT_11B_METHOD_ENUM
	int     dc_removal;                     //802.11 b ֱ��ȥ��. WT_DC_REMOVAL_ENUM
	int     eq_taps;                        //802.11 b ��������. WT_EQ_ENUM
	int     cck_ph_corr;                    //802.11 b ��λ����. WT_PH_CORR_11b_ENUM

	int     bt_Rate;                        //Bluetooth����, WT_BT_DATARATE
	int     bt_packet_type;                 //Bluetooth������, WT_BT_PACKETTYPE(Ĭ������ΪWT_BT_PACKETTYPE_NULL����)

	int     TimeoutWaiting;                 //�ڶ���������£��ȴ������ʱ�䣬Ĭ��ֵΪ8�룬��λsec
} MIMOVsaParameter;

typedef struct
{
	double  freq;                           //VSG�ز�Ƶ��,��λ��Hz
	double  power[MAX_TESTER_COUNT];        //VSG����,dBm
	int     rfPort[MAX_TESTER_COUNT];       //ָ��VSGʹ�õ�RF�˿�

	int     waveType;                       //Wave���ͣ�WT_SIGNAL_ENUM. SIG_USERFILE: ��ȡ����wave�ļ�; SIG_TESTERFILE:ʹ�������洢��wave�ļ�(WT-208�̼��汾���ڻ����3.0.1.10�Ĳ�֧�ָ���); (����ѡ���SIG_USERFILE��SIG_TESTERFILE�����ѡ�����WT-208����֧��)
	char    *wave;                          //VSG�����ļ�,���Ϊnull,ֻ�����豸���ã�������wave�ļ���������repeat��wave_gap
	int     repeat;                         //ѭ�����ʹ���
	double  wave_gap;                       //���η��ͼ��,us

	int     TimeoutWaiting;                 //�ڶ���������£��ȴ������ʱ�䣬Ĭ��ֵΪ8�룬��λsec
} MIMOVsgParameter;

//******************************************************************************
// Name:      WT_MIMO_InitMaxCaptureTime
// Func:      ��ʼ��120MHz��������֧�ֵ�������ʱ��.
//            ע��: �ýӿ�Ϊ��ѡ���ã�������ã������ڸ��ĵ�������API֮ǰ����,
//            �Ҵ˺���ֻ�ܵ���һ��.
//            ���û�е��øýӿ�,��Ĭ��֧�ֵĲ���ʱ��Ϊ10000us.
// Path:      WT_MIMO_InitMaxCaptureTime
// Access:    public
// Returns:   WT_MIMO_DLL_API void
// Parameter: int maxCaptureTimeUs:  ������ʱ��,��λ: us(΢��)
//******************************************************************************
WT_MIMO_DLL_API void CALL_MODE WT_MIMO_InitMaxCaptureTime(int maxCaptureTimeUs);

//******************************************************************************
// Name:      WT_MIMO_Initilaze
// Func:      ��ʼ��WTtester API����ע��: �ڵ��ø��ĵ�������API֮ǰ����øýӿ�,
//            �Ҵ˺���ֻ�ܵ���һ��.
// Path:      WT_MIMO_Initilaze
// Access:    public
// Returns:   WT_MIMO_DLL_API void
// Parameter: void
//******************************************************************************
WT_MIMO_DLL_API void CALL_MODE WT_MIMO_Initilaze(void);

//******************************************************************************
// Name:      WT_MIMO_Terminate
// Func:      �ͷ�WT_MIMO_Ex API����
//            ǿ�ҽ����ڷ�������֮��ŵ��øýӿڣ����������������ڴ洦�����,
//            �Ҵ˺���ֻ�ܵ���һ��.
// Path:      WT_MIMO_Terminate
// Access:    public
// Returns:   WT_MIMO_DLL_API void
// Parameter: void
//******************************************************************************
WT_MIMO_DLL_API void CALL_MODE WT_MIMO_Terminate(void);

//******************************************************************************
// Name:      WT_MIMO_Connect4Tester
// Func:      ����ָ����4̨������(WTtester)
// Path:      WT_MIMO_Connect4Tester
// Access:    public
// Returns:   WT_MIMO_DLL_API int��
//                WT_ERR_CODE_CODE_OK:�����ɹ�
//                WT_ERR_CODE_CODE_CONNECT_FAIL:����ʧ��
// Parameter: char * ipAddr1:  ������IP��ַ������ipAddr1="192.168.10.1"
// Parameter: char * ipAddr2:  ������IP��ַ������ipAddr2="192.168.10.2"
// Parameter: char * ipAddr3:  ������IP��ַ������ipAddr3="192.168.10.3"
// Parameter: char * ipAddr4:  ������IP��ַ������ipAddr4="192.168.10.4"
// Parameter: int * connID��   ����ID��ʶ, ���ں���Դ����Ӳ���ʶ��.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_Connect4Tester(char *ipAddr1, char *ipAddr2, char *ipAddr3, char *ipAddr4, int *connID);

//******************************************************************************
// Name:      WT_MIMO_Connect3Tester
// Func:      ����ָ����3̨������(WTtester)
// Path:      WT_MIMO_Connect3Tester
// Access:    public
// Returns:   WT_MIMO_DLL_API int��
//                WT_ERR_CODE_CODE_OK:�����ɹ�
//                WT_ERR_CODE_CODE_CONNECT_FAIL:����ʧ��
// Parameter: char * ipAddr1:  ������IP��ַ������ipAddr1="192.168.10.1"
// Parameter: char * ipAddr2:  ������IP��ַ������ipAddr2="192.168.10.2"
// Parameter: char * ipAddr3:  ������IP��ַ������ipAddr3="192.168.10.3"
// Parameter: int * connID��   ����ID��ʶ, ���ں���Դ����Ӳ���ʶ��.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_Connect3Tester(char *ipAddr1, char *ipAddr2, char *ipAddr3, int *connID);

//******************************************************************************
// Name:      WT_MIMO_Connect2Tester
// Func:      ����ָ����2̨������(WTtester)
// Path:      WT_MIMO_Connect2Tester
// Access:    public
// Returns:   int��
//                WT_ERR_CODE_CODE_OK:�����ɹ�
//                WT_ERR_CODE_CODE_CONNECT_FAIL:����ʧ��
// Parameter: char * ipAddr1:  ������IP��ַ������ipAddr1="192.168.10.1"
// Parameter: char * ipAddr2:  ������IP��ַ������ipAddr2="192.168.10.2"
// Parameter: int * connID��   ����ID��ʶ, ���ں���Դ����Ӳ���ʶ��.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_Connect2Tester(char *ipAddr1, char *ipAddr2, int *connID);

//******************************************************************************
// Name:      WT_MIMO_Connect1Tester
// Func:      ����ָ����1̨������(WTtester)
// Path:      WT_MIMO_Connect1Tester
// Access:    public
// Returns:   WT_MIMO_DLL_API int��
//                WT_ERR_CODE_CODE_OK:�����ɹ�
//                WT_ERR_CODE_CODE_CONNECT_FAIL:����ʧ��
// Parameter: char * ipAddr1:  ������IP��ַ������ipAddr1="192.168.10.1"
// Parameter: int * connID��   ����ID��ʶ, ���ں���Դ����Ӳ���ʶ��.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_Connect1Tester(char *ipAddr, int *connID);

//******************************************************************************
// Name:      WT_SwitchedMIMOConnect
// Func:      Switched MIMO ����������
// Path:      WT_SwitchedMIMOConnect
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//                WT_ERR_CODE_CODE_OK:�����ɹ�
//                WT_ERR_CODE_CODE_CONNECT_FAIL:����ʧ��
// Parameter: char * ipAddr:  ������IP��ַ������ipAddr1="192.168.10.1"
// Parameter: int * connID��   ����ID��ʶ, ���ں���Դ����Ӳ���ʶ��.
// Parameter: int antennaCount:  DUT��������������������
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_SwitchedMIMOConnect(char *ipAddr, int *connID, int antennaCount);

//******************************************************************************
// Name:      WT_MIMO_DisConnect
// Func:      �Ͽ����ӣ��ͷŸ�������ռ�õ�������Դ
// Path:      WT_MIMO_DisConnect
// Access:    public
// Returns:   WT_MIMO_DLL_API void
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WT_MIMO_DLL_API void CALL_MODE WT_MIMO_DisConnect(int connID);

//******************************************************************************
// Name:      WT_MIMO_GetDefaultParameter
// Func:      ����Ĭ�ϵ�VSA������mimoVsaParam,  VSG������mimoVsgParam��
//            ����������VSA��VSG֮ǰ��ִ�иò�����֮�����ڴ˻����Ͻ����޸�
// Path:      WT_MIMO_GetDefaultParameter
// Access:    public
// Returns:   WT_MIMO_DLL_API int:
//               WT_ERR_CODE_OK: �����ɹ�
//               WT_ERR_CODE_UNKNOW_PARAMETER����Ч�Ĳ���
// Parameter: MIMOVsaParameter * mimoVsaParam:  MIMO_VSA��ϸ����
// Parameter: MIMOVsgParameter * mimoVsgParam:  MIMO_VSG��ϸ����
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetDefaultParameter(MIMOVsaParameter *mimoVsaParam, MIMOVsgParameter *mimoVsgParam);

//******************************************************************************
// Name:      WT_MIMO_SetExternalGain
// Func:      ����(PC��WTtester���)�ⲿ���棬ͬʱ��VSA�Լ�VSG��Ч
// Path:      WT_MIMO_SetExternalGain
// Access:    public
// Returns:   WT_MIMO_DLL_API int:
//                WT_ERR_CODE_OK: �����ɹ�
//                WT_ERR_CODE_UNKNOW_PARAMETER: ��������
//                WT_ERR_CODE_CONNECT_FAIL: ����δ���������ж�
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ
// Parameter: double * extGain: �ⲿ����ֵ���飬��λdB����˳���Ӧ�����ӵ�������
//                             ע��:�˴�Ϊ�ⲿ���棬�����ⲿ˥����
//                             ǿ�ҽ���ʹ��ʵ������ֵ����ֵ���ù�����ܻᵼ��VSA��VSG����쳣.
// Parameter: int extGainLen: extGain����ĳ��ȣ�һ��Ϊ��Ҫ���õ���������
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetExternalGain(int connID, double *extGain, int extGainLen);


//******************************************************************************
// Name:      WT_MIMO_SetVSA
// Func:      ����MIMO_VSA����
// Path:      WT_MIMO_SetVSA
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//               WT_ERR_CODE_OK:�����ɹ�
//               WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//               WT_ERR_CODE_UNKNOW_PARAMETER:��������
//               WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: MIMOVsaParameter * vsaParam: MIMO_VSA��ϸ����
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetVSA(int connID, MIMOVsaParameter *vsaParam);

//******************************************************************************
// Name:      WT_MIMO_SetVSG
// Func:      ����MIMO_VSG����
// Path:      WT_MIMO_SetVSG
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//               WT_ERR_CODE_OK:�����ɹ�
//               WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//               WT_ERR_CODE_UNKNOW_PARAMETER:��������
//               WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: MIMOVsgParameter * vsgParam: MIMO_VSA��ϸ���ò���
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetVSG(int connID, MIMOVsgParameter *vsgParam);

//******************************************************************************
// Name:      WT_MIMO_SetVSA_AutoRange
// Func:      ����VSA�������Զ�ƥ��ο���ƽֵ(Max Power Level),����ƥ��ɹ�֮�����õ�WTtester��ȥ
//            ǿ�ҽ����������ź�δ֪��ǰ���£�����ʹ�øýӿ�
// Path:      WT_MIMO_SetVSA_AutoRange
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//               WT_ERR_CODE_OK:�����ɹ�
//               WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//               WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//               WT_ERR_CODE_UNKNOW_PARAMETER:��������
//               WT_ERR_CODE_TIMEOUT:������ʱ
//               WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: MIMOVsaParameter * vsaParam: MIMO_VSA��ϸ�����������óɹ�֮�󣬻᷵���µĲο���ƽֵ
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetVSA_AutoRange(int connID, MIMOVsaParameter *vsaParam);

//******************************************************************************
// Name:      WT_MIMO_DataCapture
// Func:      ����ָ����VSA������������ץȡ
// Path:      WT_MIMO_DataCapture
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_DataCapture(int connID);

//******************************************************************************
// Name:      WT_MIMO_StopDataCapture
// Func:      ֹͣ�ɼ�����
// Path:      WT_MIMO_StopDataCapture
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_StopDataCapture(int connID);

//******************************************************************************
// Name:      WT_MIMO_GetResult
// Func:      ��ȡָ��parameter�ķ����������ȡ�ɹ��󣬸��������ֵ����Ч.
//              ע��:�ò����ǰ��Ϊ�Ѿ�ץȡ�����������(���ȵ��ýӿ�DataCapture)
// Path:      WT_MIMO_GetResult
// Access:    public
// Returns:   int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_NO_DATA_CAPTURED:δץȡ����
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char * anaParmString: �������(�ַ�������)������WT_RES_EVM_ALL
// Parameter: double * result: ��Ӧ����洢����
// Parameter: int resultLength: result���鳤�ȣ�һ��Ϊ����Ҫ��ȡ�������������
// Parameter: char * description: ������ֵ�Ķ�Ӧ����
// Parameter: char * unit: ������ֵ�Ķ�Ӧ�ĵ�λ
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetResult(int connID, char *anaParmString, double *result, int resultLength, char *description, char *unit);

//******************************************************************************
// Name:      WT_MIMO_GetVectorResult
// Func:      ��ȡָ��parameter�ķ����������ȡ�ɹ��󣬸��������ֵ����Ч.
//              ע��:�ò����ǰ��Ϊ�Ѿ�ץȡ�����������(���ȵ��ýӿ�DataCapture)���ý�������������ʽ����
// Path:      WT_MIMO_GetVectorResult
// Access:    public
// Returns:   WT_MIMO_DLL_API int: ����ʵ�ʸ��Ƶ�����洢������Ŀ����Ԫ��С�������resultTypeΪ׼������0�������������߷���ʧ��
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int streamIndex���ڼ�����..��0��ʼ
// Parameter: char * anaParmString���������(�ַ�������)������WT_RES_EVM_ALL.
// Parameter: void * result: ��Ӧ����Ĵ洢��ַ.
// Parameter: int resultType����Ӧ�����result�����������ͣ��μ� WT_RESULT_DATA_TYPE.
// Parameter: int resultSize����Ӧ�����result���洢����Ĵ�С.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetVectorResult(int connID, int streamIndex, char *anaParmString, void *result, int resultType, int resultSize);

//******************************************************************************
// Name:      WT_MIMO_GetVectorResultElementSize
// Func:      ��ȡ�����ÿ����Ԫ���ݵĴ�С����λ���ֽ�
// Path:      WT_MIMO_GetVectorResultElementSize
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_NO_DATA_CAPTURED:δץȡ����
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char * anaParmString���������(�ַ�������)������WT_RES_EVM_ALL.
// Parameter: int * elementSize�������Ԫ���ݵĴ�С
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetVectorResultElementSize(int connID, char *anaParmString, int *elementSize);

//******************************************************************************
// Name:      WT_MIMO_GetVectorResultElementCount
// Func:      ��ȡ������������ĳ���
// Path:      WT_MIMO_GetVectorResultElementCount
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_NO_DATA_CAPTURED:δץȡ����
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char * anaParmString���������(�ַ�������)������WT_RES_EVM_ALL.
// Parameter: int * elementCount���������ĳ���
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetVectorResultElementCount(int connID, char *anaParmString, int *elementCount);

//******************************************************************************
// Name:      WT_MIMO_StartVSG
// Func:      ����ָ����VSG���������ź�(wave)���ͣ����ڷ�����ɺ�ŷ���(ͬ������)
//             ע�⣺�����ʹ�����Ϊ0�����޴�ʱ��,��API���������У������˳�
// Path:      WT_MIMO_StartVSG
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_TxInaccuracy:TX���ʲ�׼ȷ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_StartVSG(int connID);

//******************************************************************************
// Name:      WT_MIMO_AsynStartVSG
// Func:      ����ָ����VSG���������ź�(wave)���ͣ����������·���ֱ�ӷ���(�첽����)
// Path:      WT_MIMO_AsynStartVSG
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_TxInaccuracy:���͹��ʲ�׼ȷ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_AsynStartVSG(int connID);

//******************************************************************************
// Name:      WT_MIMO_GetVSGCurrentState
// Func:      ��ȡVSG��ǰ״̬.
// Path:      WT_MIMO_GetVSGCurrentState
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int * state: VSG״̬����ָ��.VSG״̬���:enum WT_VSG_STATE
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetVSGCurrentState(int connID, int *state);

//******************************************************************************
// Name:      WT_MIMO_StopVSG
// Func:      ֹͣVSG.
// Path:      WT_MIMO_StopVSG
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_StopVSG(int connID);

//******************************************************************************
// Name:      WT_MIMO_GetTesterVersion
// Func:      ��ȡ��Ӧ�Ĳ����ǵİ汾�Լ�����������.
// Path:      WT_MIMO_GetTesterVersion
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL: ����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: u32BufSize��С���������߻�δ����ָ���Ĳ�����
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int index: �ڼ�̨��������0��ʼ
// Parameter: TesterInfo * buffer:װ�ذ汾��Ϣ������,װ�ؽ�����stTesterInfo
// Parameter: int * bufferSize: ָ�������Ĵ�С
// Parameter: int * testerType����������,���WT_TESTER_TYPE
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetTesterVersion(int connID, int index, TesterInfo *buffer, int bufferSize, int *testerType);

//******************************************************************************
// Name:      WT_MIMO_GetTesterSpecification
// Func:      ��ȡ�������
// Path:      WT_MIMO_GetTesterSpecification
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: testerSpec Ϊ��
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int index: �ڼ�̨��������0��ʼ
// Parameter: DeviceSpecification * testerSpec��Tester����ŵ�ַ
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetTesterSpecification(int connID, int index, DeviceSpecification *testerSpec);
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetTesterSpecification208C(int connID, int index, Device208CSpecification *testerSpec);

//******************************************************************************
// Name:      WT_MIMO_GetTesterConnStataus
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
// Path:      WT_MIMO_GetTesterConnStataus
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              0:�����޷�����
//              !0:pu8Bufװ�ص���Ч���ݵĳ���
// Parameter: char * ipAddr: �ַ�����װ��Ŀ���豸IP����"192.168.10.254"
// Parameter: char * buffer: ���ز���������ַ��������豸���ɷ���.
// Parameter: int bufferSize: buffer�Ĵ�С
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetTesterConnStataus(char *ipAddr, char *buffer, int bufferSize);

//******************************************************************************
// Name:      WT_MIMO_SetBandwidthMode
// Func:      ���ô���ʶ��ģʽ
// Path:      WT_MIMO_SetBandwidthMode
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER����������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int bandwidthDetect: ����ģʽ, �ο� WT_BANDWIDTH_DETECT_ENUM ö��
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetBandwidthMode(int connID, int bandwidthDetect);

//******************************************************************************
// Name:      WT_MIMO_SetZigBeeAnalysisOptimise
// Func:      ZigBee�����Ż�ѡ��
// Path:      WT_MIMO_SetZigBeeAnalysisOptimise
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
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetZigBeeAnalysisOptimise(int connID, int AnalysisOptimise);

//******************************************************************************
// Name:      WT_MIMO_GetSymbolsEvm
// Func:      ��ȡĳ��Symbol��Χ�ڵ�Evm��ֵ
// Path:      WT_MIMO_GetSymbolsEvm
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER����������
//              WT_ERR_CODE_GENERAL_ERROR����ȡ���ʧ��
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int streamIndex: �ڼ�����, ��0��ʼ.
// Parameter: int startSymbol: ��ʼSymbol��ţ���0��ʼ.
// Parameter: int endSymbol: ����Symbol��ţ�����ʱ��������Symbol.
// Parameter: int evmResultType: �趨ȡ�������͵�evm���������enum SYMBOLS_EVM_RESULT_TYPE.
// Parameter: double * evmResult(Out): �洢�涨Symbol��Χ�ڵ�Evm��ֵ�Ļ��棬��λdB.
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetSymbolsEvm(int connID, int streamIndex, int startSymbol, int endSymbol, int evmResultType, double *evmResult);

//******************************************************************************
// Name:      WT_MIMO_DataStore
// Func:      ����Vsa�ź�����
// Path:      WT_MIMO_DataStore
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_GENERAL_ERROR: ����ʧ��
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char * fileName���洢���ļ���
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_DataStore(int connID, char *fileName);

//******************************************************************************
// Name:      WT_MIMO_AnalyzeCmimoReferenceData
// Func:      CMIMO�����·���DUT�����߷����źŵĲο�����
// Path:      WT_MIMO_AnalyzeCmimoReferenceData
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: antenna���ó���3��С��0
//              WT_ERR_CODE_GENERAL_ERROR: ����ʧ�ܣ�ԭ������ǻ�ûץȡ���ݻ�ץȡ������������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int antenna���ڼ������ߣ���0��ʼ��0-3��
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_AnalyzeCmimoReferenceData(int connID, int antenna);

//************************************
// Method:    WT_MIMO_GetCmimoResult
// Func:      ��ȡCMIMO��������ؽ��
// Path:      WT_MIMO_GetCmimoResult
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: antenna���ó���3��С��0
//              WT_ERR_CODE_GENERAL_ERROR: ����ʧ�ܣ�ԭ������ǻ�û�ж�Ӧ�ο��ļ�������ץȡ������������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int streamIndex: �ڼ�����, ��0��ʼ
// Parameter: char * anaParmString(in)���������(�ַ�������)������WT_RES_EVM_ALL
// Parameter: double * result(out)����Ӧ���ֵ
// Parameter: char * description(out)���ý��ֵ�Ķ�Ӧ����
// Parameter: char * unit(out)���ý��ֵ�Ķ�Ӧ�ĵ�λ
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_GetCmimoResult(int connID, int streamIndex, char *anaParmString, double *cmimoResult, char *description, char *unit);

//******************************************************************************
// Name:      WT_MIMO_LoadCmimoReferenceData
// Func:      CMIMO�����£������źŶ�Ӧ�Ĳο��ļ�
// Path:      WT_MIMO_LoadCmimoReferenceData
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: pu8FileNameΪ��
//              WT_ERR_CODE_GENERAL_ERROR: ����ʧ�ܣ�ԭ��������ļ���ʽ����
// Parameter: int connID(in): ����ʱ��ȡ��ID��ʶ.
// Parameter: char * pu8FileName(in): ���ص��ļ���������·����
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_LoadCmimoReferenceData(int connID, char *pu8FileName);

//******************************************************************************
// Name:      WT_MIMO_SaveCmimoReferenceData
// Func:      CMIMO�����±����źŶ�Ӧ�Ĳο�����
//            ע����Ҫ֮ǰ�ɹ����ɲο�����
// Path:      WT_MIMO_SaveCmimoReferenceData
// Access:    public
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: pu8FileNameΪ��
//              WT_ERR_CODE_GENERAL_ERROR: ����ʧ�ܣ�ԭ��������ļ���ʽ����
// Parameter: int connID(in): ����ʱ��ȡ��ID��ʶ.
// Parameter: char * pu8FileName(in): ������ļ���������·����
//******************************************************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SaveCmimoReferenceData(int connID, char *pu8FileName);

//************************************
// Method:    WT_MIMO_SetSpectrumMaskErrorAnalyzeRange
// Func:      ����Ƶ��ģ������ʷ����ķ�Χ��Ĭ��ȫƵ�η�����
//            ����Ҫ�����м�40M����Χ��Ƶ�״����ʣ�startFrequency��Ϊ-20��endFrequency��Ϊ20
// Path:      WT_MIMO_SetSpectrumMaskErrorAnalyzeRange
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int channelIndex: ��Ҫ����������ͨ����ţ�����Ҫ������1̨�����ɵ����źţ���ֵ����Ϊ0
// Parameter: int startFrequency����������ʼƵ��ֵ
// Parameter: int endFrequency�������Ľ���Ƶ��ֵ
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetSpectrumMaskErrorAnalyzeRange(int connID, int channelIndex, int startFrequency, int endFrequency);

//************************************
// Method:    WT_MIMO_SetSpectrumMaskVersion
// Func:      ����Ƶ��ģ��汾��ֻ������11n
// Path:      WT_MIMO_SetSpectrumMaskVersion
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: versionΪ��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int version��Ƶ��ģ��汾����Ӧö��SPECTRUM_MASK_VERSION
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetSpectrumMaskVersion(int connID, int version);

//************************************
// Method:    WT_MIMO_SetAnalyzeFrameIndex
// Func:      ���÷����ڼ�֡�ź�
// Path:      WT_MIMO_SetAnalyzeFrameIndex
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: ��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int analyzeFrameIndex���ڼ�֡�źţ���0��ʼ
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetAnalyzeFrameIndex(int connID, int analyzeFrameIndex);

//************************************
// Method:    WT_MIMO_SetZWaveRate
// Func:      ����ZWave����
// Path:      WT_MIMO_SetZWaveRate
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: zWaveRate��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: int zWaveRate��ZWave Rate����Ӧö��ZWAVE_RATE_ENUM
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetZWaveRate(int connID, int zWaveRate);

//************************************
// Method:    WT_MIMO_ExecInternalCmd
// Func:      ִ���ڲ�����
// Path:      WT_MIMO_ExecInternalCmd
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: zWaveRate��������
// Parameter: char *ipAddr: �ַ�����װ��Ŀ���豸IP����"192.168.10.254"
// Parameter: char *cmd: ��Ҫִ�е�����.
// Parameter: int cmdLen�������.
// Parameter: char *buffer: �������.
// Parameter: char *bufferSize: �����С.
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_ExecInternalCmd(char *ipAddr, char *cmd, int cmdLen, char *buffer, int bufferSize);

//************************************
// Method:    WT_MIMO_SetLrwpanFskAnalyzeParam
// Func:      ����LrwpanFsk��������
// Path:      WT_MIMO_SetLrwpanFskAnalyzeParam
// Access:    public 
// Returns:   WT_MIMO_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER: pLrwpanFskParam��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: LrwpanFskParam *pLrwpanFskParam��LrwpanFsk��������
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_SetLrwpanFskAnalyzeParam(int connID, LrwpanFskParam *pLrwpanFskParam);

//************************************
// Method:    WT_MIMO_AuthenGet
// Func:      ��ȡ��֤�ַ���ֻ��WT208H��Ч
// Path:      WT_MIMO_AuthenGet
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER����������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char *buffer��������֤�ַ��Ļ���
// Parameter: int bufferSize�������С
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_AuthenGet(int connID, char *buffer, int bufferSize);

//************************************
// Method:    WT_MIMO_AuthenSet
// Func:      �·����ܺ���ַ���ֻ��WT208H��Ч
// Path:      WT_MIMO_AuthenSet
// Access:    public 
// Returns:   WTtester_DLL_API int
//              WT_ERR_CODE_OK: ������ȫ��ȷ����֤ͨ��
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER����������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: char *buffer����������ַ��Ļ���
// Parameter: int dataLen�������ַ�����
//************************************
WT_MIMO_DLL_API int CALL_MODE WT_MIMO_AuthenSet(int connID, char *buffer, int bufferSize);

#endif

