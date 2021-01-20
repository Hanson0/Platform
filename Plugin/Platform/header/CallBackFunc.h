#pragma once

enum OperateType
{
	eumElement_read,	//读取
	eumElement_write,	//写入
};

enum CfgType
{
	CFG_BT_Limit,		//来源于WT_BT_LIMIT
	CFG_Dut_Mimo,		//来源于WT_DUT_MIMO
	CFG_Flow,			//来源于WT_FLOW
	CFG_Mac,			//来源于WT_MAC
	CFG_Tester,			//来源于WT_TESTER
	CFG_Wifi_Limit,		//来源于WT_WIFI_LIMIT
	CFG_Zigbee_Limit,	//来源于WT_ZIGBEE_LIMIT
	CFG_Atten_Dut,		//来源于WT_ATTEN_DUT_X
	CFG_Platform_Info	//来源于平台
};

enum PrintType
{
	Enum_Title,			//打印到标题栏
	Enum_Text,			//打印到主页面和log中
	Enum_Error,			//打印到主页面和log中,以红色字体输出
	Enum_Debug			//调试打印，只有修改debug.ini后才显示到主页面和log
};

//******************************************************************************
// Name		：PrintLogCB
// Func     ：打印信息到界面的函数指针
// Path     ：PrintLogCB
// Access   ：public
// Returns  ：void
// Parameter: dutId:当前的ID
//			  printfType:选择要打印的类型，详细见枚举 PrintType
//			  printfContent:输出的内容
//******************************************************************************
typedef void (*PrintLogCB)(int dutId, int printfType, const char *printfContent);

//******************************************************************************
// Name     ：IsStopRunningCB
// Func     ：获取stop标志位的函数指针
// Path     ：IsStopRunningCB
// Access   ：public
// Returns  ：void
// Parameter: dutId:当前的ID
//******************************************************************************
typedef bool (*IsStopRunningCB)(int dutId);

//******************************************************************************
// Name     ：CfgElementOperationCB
// Func     ：读取和写入配置文件字符串的函数指针
// Path     ：CfgElementOperationCB
// Access   ：public
// Returns  ：void
// Parameter: dutId:当前的ID
//			  type:选择对配置容器的操作，详细见枚举 OperateType
//			  key:读取的信息对应的关键字
//			  value:读取或写入的值
//			  valueSize:读取或写入的值的大小
//******************************************************************************
typedef bool (*CfgElementOperationCB)(int dutId, int opType, int cfgType, const char* key, char* value, int valueSize);

//******************************************************************************
// Name		：CfgArrayElementOperationCB
// Func		：读取和写入配置文件字符串数组的函数指针
// Path		：CfgArrayElementOperationCB
// Access	：public
// Returns	：void
// Parameter: dutId:当前的ID
//			  type:选择对配置容器的操作，详细见枚举 OperateType
//			  key:读取的信息对应的关键字
//			  value:读取或写入的值
//			  valueSize:读取或写入的值的大小
//			  elemIndex:读取或写入数组内第几个元素
//******************************************************************************
typedef bool (*CfgArrayElementOperationCB)(int dutId, int opType, int cfgType, const char* key, char* value, int valueSize, int elemIndex);

struct CallBackManager
{
	PrintLogCB printLog;									//打印回调函数
	IsStopRunningCB isStopRunning;							//获取Stop标志回调函数
	CfgElementOperationCB cfgElementOperation;				//读写配置容器回调函数
	CfgArrayElementOperationCB cfgArrayElementOperation;	//读写数组配置容器回调函数
};
