// DUTTEst.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "DutDefine.h"

DUT_NAMESPACE_BEGIN
DUT_FUNC IDut *CreatePlugin()
{
	DUT_CONTROL *pDutControl = new DUT_CONTROL();

	return pDutControl;
}

DUT_FUNC void DestroyPlugin(IDut *plugin)
{
	delete (DUT_CONTROL*)plugin;
}

DUT_FUNC void GetPluginVersion(char *version, int verSize)
{
	strcpy_s(version, verSize, DUT_PLUGIN_VERSION);
}

DUT_NAMESPACE_END
