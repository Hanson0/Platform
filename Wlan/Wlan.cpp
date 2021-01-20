// 这是主 DLL 文件。

#include "stdafx.h"

#include "Wlan.h"

using namespace System;
using namespace System::Text;
using namespace AILinkFactoryAuto::Task::Wlan::Executer;
using namespace AILinkFactoryAuto::Task::Wlan::Property;
using namespace AILinkFactoryAuto::Task;
using namespace AILinkFactoryAuto::Utils;
using namespace AILinkFactoryAuto::Core;
using namespace AILinkFactoryAuto::Task::Property;
using namespace AILinkFactoryAuto::Task::Executer;
using namespace AILinkFactoryAuto::Wlan::Plugin;
using namespace AILinkFactoryAuto::Task::Wlan::Utils;
using namespace AILinkFactoryAuto::Instrument::WtApi;

int WtUtils::WtMcs2Int(WtMcs wtMcs)
{
	int ret = 0;

	if (wtMcs <= WtMcs::MCS_11M)
	{
		ret = (int)wtMcs;
	}
	else if (wtMcs <= WtMcs::MCS_54M)
	{
		ret = (int)wtMcs - (int)WtMcs::MCS_6M;
	}
	else if (wtMcs <= WtMcs::MCS11)
	{
		ret = (int)wtMcs - (int)WtMcs::MCS0;
	}

	return ret;
}

void LoadDllExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	LoadDllProperties^ config = (LoadDllProperties^)properties;
	ILog^ log = globalDic->Get<ILog^>();
	DutFrame::Log = log;
	//log->Info("打印在测试界面");
	//LogUtils::UiDebug->Info(gcnew String("打印在debug窗口"));
	DutFrame::InfoType = config->InfoType;
	DutFrame^ dutFrame = gcnew DutFrame(gcnew String(config->Filename));
	log->Info(String::Format("load {0} success", config->Filename));
	LogUtils::UiDebug->Info(String::Format("load {0} success", config->Filename));
	
	dutFrame->GetPluginVersion();
	DutFrame::WtSetUpDic->Add(String::Format("DUT{0}", config->Sequence), config->WtSetUp);
	dutFrame->SetDutId(config->Sequence);
	dutFrame->SetCallBack();
	//dutFrame->Init();
	//dutFrame->Open(WtDut::WT_DUT_GENERICITY);

	globalDic->Put(dutFrame);
	LogUtils::UiDebug->Info("globalDic->Put(dutFrame)");
}

//void WtSetUpExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
//{
//	WtSetUpProperties^ config = (WtSetUpProperties^)properties;
//	DutFrame::WtSetUpDic->Add(String::Format("DUT{0}", config->Sequence) , config->WtSetUp);
//}

void DutInitExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	dutFrame->Init();
}

void IsDutReadyExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	bool ret = dutFrame->IsDutReady();
	if (!ret)
	{
		throw gcnew Exception("dut is not ready");
	}
}

void OpenDutExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	OpenDutProperties^ config = (OpenDutProperties^)properties;
	dutFrame->Open(config->WtDut);
}

void CloseDutExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	CloseDutProperties^ config = (CloseDutProperties^)properties;
	dutFrame->Close(config->WtDut);
}

CloseDutProperties::CloseDutProperties()
{
	this->RetryCount = 0;
	this->ExecuteCondition = AILinkFactoryAuto::Task::Property::ExecuteCondition::ALWAYS;
}

void ConnectInstrumentExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	ConnectInstrumentProperties^ config = (ConnectInstrumentProperties^)properties;
	WlanTester::WtDllInitialize();
	WlanTester^ wlanTester = gcnew WlanTester();
	wlanTester->WtConnect(config->ip);
	WtInfo^ wtInfo = wlanTester->WtGetTesterVersion();
	ILog^ log = globalDic->Get<ILog^>();
	log->Info(String::Format("IP地址：{0}", wtInfo->Ip));
	log->Info(String::Format("子网掩码：{0}", wtInfo->SubMask));
	log->Info(String::Format("网关：{0}", wtInfo->GateAddr));
	log->Info(String::Format("SN码：{0}", wtInfo->Sn));
	log->Info(String::Format("别名：{0}", wtInfo->Name));
	log->Info(String::Format("MAC地址：{0}", wtInfo->MacAddr));
	log->Info(String::Format("固件版本：{0}", wtInfo->FwVersion));
	log->Info(String::Format("硬件版本：{0}", wtInfo->HwVersion));
	log->Info(String::Format("射频板版本：{0}", wtInfo->RfVersion));
	log->Info(String::Format("校准日期：{0}", wtInfo->CalDate));
	globalDic->Put(wlanTester);
}

void DisconnectInstrumentExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	WlanTester^ wlanTester = globalDic->Get<WlanTester^>();
	if (wlanTester != nullptr)
	{
		wlanTester->WtDisConnect();
	}
}

void CalBeginExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	CalBeginProperties^ config = (CalBeginProperties^)properties;
	dutFrame->CalBegin(config->WtDut);
}

void CalEndExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	CalEndProperties^ config = (CalEndProperties^)properties;
	dutFrame->CalEnd(config->WtDut);
}

void TempratureCompenstationExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	dutFrame->TempratureCompensation();
}

void SetMacAddressExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	ILog^ log = globalDic->Get<ILog^>();
	GlobalVaribles^ gv = globalDic->Get<GlobalVaribles^>();

	WtMacType type = WtMacType::eumMacIdx_Wifi;
	String^ macSet = gv->Get(GlobalVaribles::MAC);

	log->Info("Set MAC=" + macSet);
	dutFrame->SetMac(type, macSet);

	StringBuilder^ macGet = gcnew StringBuilder();
	dutFrame->GetMac(type, macGet);
	log->Info("Get MAC=" + macGet);

	if (macSet != macGet->ToString())
	{
		log->Fail("set mac is different from get mac");
	}
}

void SaveCalDataExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	dutFrame->SaveCalData();
}

void WriteEfuseExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	WriteEfuseProperties^ config = (WriteEfuseProperties^)properties;
	dutFrame->WriteEfuse(config->WtDut);
}

void CheckEfuseExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	CheckEfuseProperties^ config = (CheckEfuseProperties^)properties;
	dutFrame->CheckEfuse(config->WtDut);
}