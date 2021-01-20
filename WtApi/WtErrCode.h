#pragma once

namespace AILinkFactoryAuto {
	namespace Instrument {
		namespace WtApi {

			public enum class WtErrCode
			{
				WT_ERR_CODE_OK,
				WT_ERR_CODE_CONNECT_FAIL,            //����ʧ�ܡ�δ���������ж�
				WT_ERR_CODE_UNKNOW_PARAMETER,        //��������
				WT_ERR_CODE_OUT_OF_MEMORY,           //�ڴ治��
				WT_ERR_CODE_NO_DATA_CAPTURED,        //δץȡ����
				WT_ERR_CODE_TIMEOUT,                 //��ʱ
				WT_ERR_CODE_VsgInaccuracy,           //ָ����VSG���ʲ�׼ȷ
				WT_ERR_CODE_GENERAL_ERROR,           //��������

				WT_ERR_CODE_BANDWIDTH_ERROR,         //�������ô���
				WT_ERR_CODE_SIGNALTYPE_ERROR,        //�ź����ʹ���
				WT_ERR_CODE_FRM_ERROR,               //11n֡���ʹ���
				WT_ERR_CODE_PARAMETER_MISMATCH,      //������������
				WT_ERR_CODE_PSDU_ERROR,              //PSDU���ô���
				WT_ERR_CODE_PSDU_CONVERT_FAIL,       //Mac��ʽ����
				WT_ERR_CODE_OUTDATA_INVALID,         //���������ݵ�ָ�����
				WT_ERR_CODE_GENERATE_FAIL,           //�����ź�ʧ��

				WT_ERR_CODE_TESTER_NO_WAVE,          //����û��ָ���Ĳ����ļ�
				WT_ERR_CODE_NO_LICENSE_SUPPORT,      //û�ж�Ӧ��license֧��

				WT_ERR_CODE_TX_WAIT_RESOURCE_TIMEOUT, //TX����Ӳ����Դʧ��
				WT_ERR_CODE_RX_WAIT_RESOURCE_TIMEOUT, //RX����Ӳ����Դʧ��

				WT_ERR_CODE_AUTHEN_FAIL,              //��֤ʧ��

				WT_ERR_CODE_LAST
			};
		}
	}
}