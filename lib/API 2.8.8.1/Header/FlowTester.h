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
	double interval_from_last_operate;        //���ϸ�VSA�����ļ��. ms
	double sample_freq;                  //�������ʣ�Hz��108��208C֧��15M,30M,60M,120M,����ֻ֧��120M
	double attenuation;                  //�ⲿ˥����dB
	double freq;               //VSA�ز�Ƶ��,��λ��Hz
	double max_power;          //����������,dBm; (�����ʵ������������Ĺ��ʻ������ټ�12dB��������չ��ʷ�Χδ֪����������Auto Range)
	double smp_time;           //����ʱ��,us
	int rfPort;             //ָ��VSAʹ�õ�RF�˿�

	int trig_type;          //����ģʽ,WT_TRIG_TYPE_ENUM
	double trig_level;         //������ƽ,��max_power�Ĳ��,dB
	double trig_timeout;       //�����ȴ���ʱ,sec����ʱ����TimeoutWaiting��ʱ���໥������
	double trig_pretime;       //��������ʱ��,��������ǰ����ʱ���ڵ�����,us
	int reserveds[50];
}VsaControl;

typedef struct
{
	double interval_from_last_operate;        //���ϸ�VSG�����ļ��. ms
	double sample_freq;                  //�������ʣ�Hz��108��208C֧��15M,30M,60M,120M,����ֻ֧��120M
	double attenuation;                  //�ⲿ˥����dB
	double freq;               //VSG�ز�Ƶ��,��λ��Hz
	double power;              //VSG����,dBm
	int rfPort;             //ָ��VSGʹ�õ�RF�˿�
	int repeat;             //ѭ�����ʹ���
	double wave_gap;           //���η��ͼ����us
	int wave_index;             //�ڼ����źţ���0��ʼ
	int waveType;           //Wave���ͣ�WT_SIGNAL_ENUM. SIG_USERFILE: ��ȡ����wave�ļ�; SIG_TESTERFILE: ʹ�������洢��wave�ļ�(WT-208�̼��汾���ڻ����3.0.1.10�Ĳ�֧�ָ���); (����ѡ���SIG_USERFILE��SIG_TESTERFILE�����ѡ�����WT-208����֧��)
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
	int npusch_format; /*NPUSCH�ŵ���ʽ��enum NB_IOT_NPUSCH_FORMAT*/
	int resource_unit_subcarr_num; //һ����Դ��Ԫ���õ����ز���(N_RA_SC)��1��3��6��12��
	unsigned int qm; /*����ӳ��ָ����
					 resource_unit_subcarr_num=1��BPSK����QPSK��
					 resource_unit_subcarr_num>1��QPSK��
					 enum NB_IOT_NPUSCH_QM */
	int deta_f;      /*���ز������֧��3.75kHz��15kHz�������ز������enum NB_IOT_SUBCARRIER_DETA_FREQ*/
	unsigned int mcs; /*���Ʊ���ָ����deta_f(3.75kHz): 0~10��deta_f(15kHZ): 0~13��*/
	int ru_sub_carr_pos; /*RU���ز�ӳ���ƫ������
						 deta_f=3.75kHz����resource_unit_subcarr_num=1��ȡֵ0~47��
						 deta_f=15kHz��resource_unit_subcarr_num=1��ȡֵ0~11
									  resource_unit_subcarr_num=3��ȡֵ0��3��6��9��
									  resource_unit_subcarr_num=6��ȡֵ0��6��
									  resource_unit_subcarr_num=12��ȡֵ0��*/
	int cell_id;    /*NB-IOTС���� 0~503*/
	int alpha_shift;  /*resource_unit_subcarr_num>1ʱ��ѭ����λ��
					  resource_unit_subcarr_num=1��Ч��
					  resource_unit_subcarr_num=3��0,1,2,
					  resource_unit_subcarr_num=6: 0,1,2,3,
					  resource_unit_subcarr_num=12: 0��*/
	int dmrs_group_hopping_flag; /*DMRS������־λ��0-��ʹ�ܣ�1-ʹ�ܣ�*/
	int time_input_flag;     /*�������������ֶ��Ƿ������û����루0-��ʹ�ܣ�1-ʹ�ܣ�*/
	int npusch_rep_time;    /*NPUSCH�ŵ��ظ�����(1,2,4,8,16,32,64,128)*/
	int npusch_total_ru;    /*NPUSCH�ܹ����ȵ�RU��Ŀ(1,2,3,4,5,6,8,10)*/
	int reserveds[20];
}NpuschParameters;

typedef struct
{
	int preamble_format;  /*��������ŵ��ĸ�ʽ enum NB_IOT_NPRACH_FORMAT*/
	int used_subcarr_num;  /*ʹ�õ����ز�����(N_RA_SC)��12��24��36��48��*/
	int sub_carr_pos;     /*���ز�ƫ��(SC_offset)(0,12,24,36,2,18,34)*/
	int init_sc_idx;     /*���ز���ʼ������(InitSCIdx)��0~used_subcarr_num-1)*/
	int nprach_rep_time;    /*NPRACH�ŵ��ظ�����(1,2,4,8,16,32,64,128)*/
	int npusch_deta_f;      /*NPUSCH�ŵ������ز������֧��3.75kHz��15kHz�������ز������enum NB_IOT_SUBCARRIER_DETA_FREQ*/
	int cell_id;    /*NB-IOTС���� 0~503*/
	int reserveds[19];
}NprachParameters;

typedef struct
{
	int demod;              //802.11 ����ģʽ.WT_DEMOD_ENUM
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
	VsgWaves vsg_waves; /* vsa��vsg������������vsg������Ҫ�õ����ź� */
	int reserved;
	int vsg_control_before_master_start_valid; /*0: vsg_control_before_master_start��Ч��1��vsg_control_before_master_start��Ч*/
	VsgControl vsg_control_before_master_start; /*���� vsa����ǰ��VSG����*/
	VsaControl vsa_master_control; /*��VSA����*/
	int vsg_control_flow_after_master_count; /*��vsa�������vsg��������*/
	int vsa_control_flow_after_master_count; /*��vsa�������vsa��������*/
	VsgControl vsg_control_flow_after_master[MAX_FLOW_COUNT]; /*��vsa�������vsg��������
															  ÿ��vsg��������������ǰһ��vsg�������ģ�
															  ��һ��vsg�����ļ���������vsa������*/
	VsaControl vsa_control_flow_after_master[MAX_FLOW_COUNT]; /*��vsa�������vsa��������
															  ÿ��vsa��������������ǰһ��vsa��������,
															  ��һ��vsa�����ļ���������vsa������*/
	int band_count; /*band �ĸ���*/
	int each_band_vsg_count[MAX_BAND_COUNT]; /*ÿ��band��vsg��������,��һ��band��vsg��������������vsg_control_before_master_start*/
	int each_band_vsa_count[MAX_BAND_COUNT]; /*ÿ��band��vsa��������,��һ��band��vsa������������vsa_master_control*/
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
// Func:      ����vsa vsg��������ֻ�ǽ��������ã����Ὺ����������vsa,vsg����
// Path:      WT_SetVsaVsgControlFlow
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_GENERAL_ERROR:������������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: VsaVsgControlFlow * controlFlow: vsa vsg����������
//************************************
FlowTester_DLL_API int CALL_MODE WT_SetVsaVsgControlFlow(int connID, VsaVsgControlFlow *controlFlow);

//************************************
// Method:    WT_SetVsaAnalyzeFrame
// Func:      �����ĸ�vsa���ź���Ϊ�����ź�Դ
// Path:      WT_SetVsaAnalyzeFrame
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER:�����������vsaFlowIndex����WT_SetVsaVsgControlFlow����ʱ������
//              WT_ERR_CODE_GENERAL_ERROR:���ô���
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: AlgParameters * alg_param�������ð��źŶ�Ӧ���㷨����
// Parameter: int vsaFlowIndex��vsa����ţ���Ŵ�0��ʼ��
//                0��ѡȡVsaVsgControlFlow.vsa_master_control�ж�Ӧ�Ĳɼ����ź�����Ϊ�����ź�Դ��
//                1-n��ѡȡVsaVsgControlFlow.vsa_control_flow_after_master�е�0-(n-1)��Ӧ��vsa�ɼ����ź�����Ϊ�����ź�Դ
//************************************
FlowTester_DLL_API int CALL_MODE WT_SetVsaAnalyzeFrame(int connID, AlgParameters *alg_param, int vsaFlowIndex);

//************************************
// Method:    WT_SetVsaAnalyzeFrameWithRange
// Func:      �����ĸ�vsa���ź���Ϊ�����ź�Դ�����趨�źŷ�������ʼ��ͽ�����
// Path:      WT_SetVsaAnalyzeFrameWithRange
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER:�����������vsaFlowIndex����WT_SetVsaVsgControlFlow����ʱ������
//              WT_ERR_CODE_GENERAL_ERROR:���ô���
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: AlgParameters * alg_param�������ð��źŶ�Ӧ���㷨����
// Parameter: int vsaFlowIndex��vsa����ţ���Ŵ�0��ʼ��
//                0��ѡȡVsaVsgControlFlow.vsa_master_control�ж�Ӧ�Ĳɼ����ź�����Ϊ�����ź�Դ��
//                1-n��ѡȡVsaVsgControlFlow.vsa_control_flow_after_master�е�0-(n-1)��Ӧ��vsa�ɼ����ź�����Ϊ�����ź�Դ
// Parameter: int frameStartInUs���ð��źŷ�������ʼ�㣬��λ��΢��
// Parameter: int validFrameLengthInUs���ð��źŷ����ĳ��ȣ���λ��΢��
//************************************
FlowTester_DLL_API int CALL_MODE WT_SetVsaAnalyzeFrameWithRange(int connID, AlgParameters *alg_param, int vsaFlowIndex, int frameStartInUs, int validFrameLengthInUs);

//************************************
// Method:    WT_AsynStartVsaVsgFlow
// Func:      �첽����vsa��vsg�������ò��轫���������������õ�vsa��vsg������vsa��vsg����
//            �ò���Ϊ�첽����������������vsa��vsgʱ�ͻ᷵�أ�����ȵ�vsa��vsg�����ŷ���
// Path:      WT_AsynStartVsaVsgFlow
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_UNKNOW_PARAMETER:��������
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_VsgInaccuracy:���͹��ʲ�׼ȷ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
//************************************
FlowTester_DLL_API int CALL_MODE WT_AsynStartVsaVsgFlow(int connID);

//************************************
// Method:    WT_GetFlowCapturedData
// Func:      ��ȡ����vsa�ɼ������ź�
// Path:      WT_GetFlowCapturedData
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_OUT_OF_MEMORY:�ڴ治��
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
//************************************
FlowTester_DLL_API int CALL_MODE WT_GetFlowCapturedData(int connID);

//************************************
// Method:    WT_GetVsaVsgFlowState
// Func:      ��ȡvsa��vsg��������״̬
// Path:      WT_GetVsaVsgFlowState
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
// Parameter: enum WT_VSA_VSG_FLOW_STATE * state: vsa��vsg״̬����ָ��.״̬���:enum WT_VSA_VSG_FLOW_STATE
//************************************
FlowTester_DLL_API int CALL_MODE WT_GetVsaVsgFlowState(int connID, enum WT_VSA_VSG_FLOW_STATE *state);

//************************************
// Method:    WT_GetDefaultVsaVsgControlFlow
// Func:      ��ȡĬ�ϵ�vsa��vsg���������ò���
// Path:      WT_GetDefaultVsaVsgControlFlow
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:�����ɹ�
// Parameter: VsaVsgControlFlow * controlFlow�������VsaVsgControlFlow��������ָ��
//************************************
FlowTester_DLL_API int CALL_MODE WT_GetDefaultVsaVsgControlFlow(VsaVsgControlFlow *controlFlow);

//************************************
// Method:    WT_GetDefaultAlgParameters
// Func:      ����alg_type ��ȡ��Ӧ���㷨Ĭ�ϲ���
// Path:      WT_GetDefaultAlgParameters
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:�����ɹ�
// Parameter: AlgParameters * algParameters���㷨�������洫��ָ��
// Parameter: enum ALG_TYPE alg_type���㷨���ͣ�ȡ���ڷ��������ź�
//************************************
FlowTester_DLL_API int CALL_MODE WT_GetDefaultAlgParameters(AlgParameters *algParameters, enum ALG_TYPE alg_type);

//************************************
// Method:    WT_StopVsaVsgFlow
// Func:      ֹͣvsa��vsg������
// Path:      WT_StopVsaVsgFlow
// Access:    public 
// Returns:   FlowTester_DLL_API int CALL_MODE
//              WT_ERR_CODE_OK:�����ɹ�
//              WT_ERR_CODE_CONNECT_FAIL:����δ���������ж�
//              WT_ERR_CODE_TIMEOUT:������ʱ
//              WT_ERR_CODE_GENERAL_ERROR:��������
// Parameter: int connID: ����ʱ��ȡ��ID��ʶ.
//************************************
FlowTester_DLL_API int CALL_MODE WT_StopVsaVsgFlow(int connID);

FlowTester_DLL_API int CALL_MODE WT_GetFlowResult(int connID);

FlowTester_DLL_API int CALL_MODE WT_GetFlowPow(int connID, int vsaFlowIndex,double *result);

FlowTester_DLL_API int CALL_MODE WT_SetNbiotAnalyzeAlgParam(int connID,AlgParameters *alg_param);


#endif