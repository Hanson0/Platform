#pragma once

enum OperateType
{
	eumElement_read,	//��ȡ
	eumElement_write,	//д��
};

enum CfgType
{
	CFG_BT_Limit,		//��Դ��WT_BT_LIMIT
	CFG_Dut_Mimo,		//��Դ��WT_DUT_MIMO
	CFG_Flow,			//��Դ��WT_FLOW
	CFG_Mac,			//��Դ��WT_MAC
	CFG_Tester,			//��Դ��WT_TESTER
	CFG_Wifi_Limit,		//��Դ��WT_WIFI_LIMIT
	CFG_Zigbee_Limit,	//��Դ��WT_ZIGBEE_LIMIT
	CFG_Atten_Dut,		//��Դ��WT_ATTEN_DUT_X
	CFG_Platform_Info	//��Դ��ƽ̨
};

enum PrintType
{
	Enum_Title,			//��ӡ��������
	Enum_Text,			//��ӡ����ҳ���log��
	Enum_Error,			//��ӡ����ҳ���log��,�Ժ�ɫ�������
	Enum_Debug			//���Դ�ӡ��ֻ���޸�debug.ini�����ʾ����ҳ���log
};

//******************************************************************************
// Name		��PrintLogCB
// Func     ����ӡ��Ϣ������ĺ���ָ��
// Path     ��PrintLogCB
// Access   ��public
// Returns  ��void
// Parameter: dutId:��ǰ��ID
//			  printfType:ѡ��Ҫ��ӡ�����ͣ���ϸ��ö�� PrintType
//			  printfContent:���������
//******************************************************************************
typedef void (*PrintLogCB)(int dutId, int printfType, const char *printfContent);

//******************************************************************************
// Name     ��IsStopRunningCB
// Func     ����ȡstop��־λ�ĺ���ָ��
// Path     ��IsStopRunningCB
// Access   ��public
// Returns  ��void
// Parameter: dutId:��ǰ��ID
//******************************************************************************
typedef bool (*IsStopRunningCB)(int dutId);

//******************************************************************************
// Name     ��CfgElementOperationCB
// Func     ����ȡ��д�������ļ��ַ����ĺ���ָ��
// Path     ��CfgElementOperationCB
// Access   ��public
// Returns  ��void
// Parameter: dutId:��ǰ��ID
//			  type:ѡ������������Ĳ�������ϸ��ö�� OperateType
//			  key:��ȡ����Ϣ��Ӧ�Ĺؼ���
//			  value:��ȡ��д���ֵ
//			  valueSize:��ȡ��д���ֵ�Ĵ�С
//******************************************************************************
typedef bool (*CfgElementOperationCB)(int dutId, int opType, int cfgType, const char* key, char* value, int valueSize);

//******************************************************************************
// Name		��CfgArrayElementOperationCB
// Func		����ȡ��д�������ļ��ַ�������ĺ���ָ��
// Path		��CfgArrayElementOperationCB
// Access	��public
// Returns	��void
// Parameter: dutId:��ǰ��ID
//			  type:ѡ������������Ĳ�������ϸ��ö�� OperateType
//			  key:��ȡ����Ϣ��Ӧ�Ĺؼ���
//			  value:��ȡ��д���ֵ
//			  valueSize:��ȡ��д���ֵ�Ĵ�С
//			  elemIndex:��ȡ��д�������ڵڼ���Ԫ��
//******************************************************************************
typedef bool (*CfgArrayElementOperationCB)(int dutId, int opType, int cfgType, const char* key, char* value, int valueSize, int elemIndex);

struct CallBackManager
{
	PrintLogCB printLog;									//��ӡ�ص�����
	IsStopRunningCB isStopRunning;							//��ȡStop��־�ص�����
	CfgElementOperationCB cfgElementOperation;				//��д���������ص�����
	CfgArrayElementOperationCB cfgArrayElementOperation;	//��д�������������ص�����
};
