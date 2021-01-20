// 这是主 DLL 文件。

#include "stdafx.h"

#include <Windows.h>
#include "DutFrame.h"
#include "SignalPlugin.h"

#define _ENABLE_LOG TRUE

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;
using namespace AILinkFactoryAuto::Wlan::Plugin;
using namespace AILinkFactoryAuto::Utils;
using namespace DutNamespace;

Signal* Convert2Signal(SignalData^ signalData)
{
	SignalPlugin* signal = new SignalPlugin();
	signal->SetPow(signalData->Pow);
	signal->SetFreqHz(signalData->Freq);
	signal->SetAntenna(signalData->Antenna);
	signal->Demod = (int)signalData->WtDemodPlugin;
	signal->Bw = (int)signalData->WtBw;

	int channel = WifiUtils::Freq2Channel(signalData->Freq / 10e6);
	signal->SetChannel(channel);
	if (channel <= 14)
	{
		signal->FreqGroup = 0;
	}
	else
	{
		signal->FreqGroup = 1;
	}
	//signal->FreqGroup = eumFreqGroupMax;
	signal->SetMcs(signalData->Mcs);
	signal->SetFreqOffsetHz(0);
	signal->SetPreamble(signalData->Preamble);
	signal->SetGi((int)signalData->WtGi);

	return signal;
}

String^ CftType2Filename(WtCfgType wtCfgType)
{
	String^ filename;
	switch (wtCfgType)
	{
	case WtCfgType::CFG_BT_Limit:
		break;

	case WtCfgType::CFG_Dut_Mimo:
		filename = "./WT_SETUP\\WT_DUT_MIMO.txt";
		break;

	case WtCfgType::CFG_Flow:
		break;

	case WtCfgType::CFG_Mac:
		break;

	case WtCfgType::CFG_Tester:
		filename = "./WT_SETUP\\WT_TESTER.txt";
		break;

	case WtCfgType::CFG_Wifi_Limit:
		filename = "./WT_SETUP\\WT_WIFI_LIMIT.txt";
		break;

	case WtCfgType::CFG_Zigbee_Limit:
		break;

	case WtCfgType::CFG_Atten_Dut:
		break;

	case WtCfgType::CFG_Platform_Info:
		break;

	default:
		break;
	}

	return filename;
}

bool CallBackIsStopRunning(int dutId)
{
	return true;
}

void CallBackPrintLog(int dutId, int printfType, const char *printfContent) 
{
	String^ content = Marshal::PtrToStringAnsi((IntPtr)(char *)printfContent);
	if (printfType == Enum_Debug)
	{
		LogUtils::UiDebug->InfoFormat("dutId={0}, printfType={1}, printfContent={2}", dutId, printfType, content);
	}
	else if (printfType == Enum_Error)
	{
		DutFrame::Log->Fail(String::Format("dutId={0}, printfType={1}, printfContent={2}", dutId, printfType, content));
	}
	else
	{
		DutFrame::Log->Info(String::Format("dutId={0}, printfType={1}, printfContent={2}", dutId, printfType, content));
	}
}

bool CallBackCfgElementOperation(int dutId, int opType, int cfgType, const char* key, char* value, int valueSize)
{
	String^ _key = Marshal::PtrToStringAnsi((IntPtr)(char *)key);
	String^ _value = Marshal::PtrToStringAnsi((IntPtr)(char *)value);
	WtOperateType wtOperateType = (WtOperateType)opType;
	WtCfgType wtCfgType = (WtCfgType)cfgType;
#if ENABLE_LOG
	DutFrame::Log->Info(String::Format("->dutId={0}, opType={1}, cfgType={2}, key={3}, value={4}, valueSize={5}",
		dutId, wtOperateType, wtCfgType, _key, _value, valueSize));
#endif	
	if (wtOperateType == WtOperateType::eumElement_read)
	{
		try
		{
			if (DutFrame::InfoType == InfoType::STUDIO)
			{
				Dictionary<String^, KeyValue^>^ wtSetUp = DutFrame::WtSetUpDic[String::Format("DUT{0}", dutId)];
				KeyValue^ keyValue = wtSetUp[_key];
				memcpy_s(value,
					keyValue->Value->Length,
					(char *)(void *)Marshal::StringToHGlobalAnsi(keyValue->Value),
					keyValue->Value->Length);
				_value = Marshal::PtrToStringAnsi((IntPtr)(char *)value);
			}
			else if (DutFrame::InfoType == InfoType::WLAN_TESER)
			{
				String^ returnValue;
				String^ filename = CftType2Filename(wtCfgType);
				
				int ret = WtInfoUtils::ReadProfileString(_key, returnValue, filename);
				if (ret != 0)
				{
					return false;
				}

				memcpy_s(value,
					returnValue->Length,
					(char *)(void *)Marshal::StringToHGlobalAnsi(returnValue),
					returnValue->Length);
			}
#if ENABLE_LOG
			DutFrame::Log->Info(String::Format("<-dutId={0}, opType={1}, cfgType={2}, key={3}, value={4}, valueSize={5}",
				dutId, wtOperateType, wtCfgType, _key, _value, valueSize));
#endif
			return true;
		}
		catch (Exception^ e)
		{
			LogUtils::UiDebug->Error(e->ToString());
		}
		return false;
	}

	return true;
}

bool CallBackCfgArrayElementOperation(int dutId, int opType, int cfgType, const char* key, char* value, int valueSize, int elemIndex)
{
	String^ _key = Marshal::PtrToStringAnsi((IntPtr)(char *)key);
	String^ _value = Marshal::PtrToStringAnsi((IntPtr)(char *)value);
	WtOperateType wtOperateType = (WtOperateType)opType;
	WtCfgType wtCfgType = (WtCfgType)cfgType;
#if ENABLE_LOG
	DutFrame::Log->Info(String::Format("<-dutId={0}, opType={1}, cfgType={2}, key={3}, value={4}, valueSize={5}, elemIndex={6}",
		dutId, wtOperateType, wtCfgType, _key, _value, valueSize, elemIndex));
#endif
	if (wtOperateType == WtOperateType::eumElement_read)
	{
		try
		{
			array<wchar_t>^ split = gcnew array<wchar_t>(1);
			split[0] = ' ';
			array<String^>^ valueArray;
			if (DutFrame::InfoType == InfoType::STUDIO)
			{
				Dictionary<String^, KeyValue^>^ wtSetUp = DutFrame::WtSetUpDic[String::Format("DUT{0}", dutId)];
				KeyValue^ keyValue = wtSetUp[_key];
				valueArray = keyValue->Value->Split(split, StringSplitOptions::RemoveEmptyEntries);
			}
			else if (DutFrame::InfoType == InfoType::WLAN_TESER)
			{
				String^ returnValue;
				String^ filename = CftType2Filename(wtCfgType);

				int ret = WtInfoUtils::ReadProfileString(_key, returnValue, filename);
				if (ret != 0)
				{
					return false;
				}

				valueArray = returnValue->Split(split, StringSplitOptions::RemoveEmptyEntries);
			}

			_value = valueArray[elemIndex];
			memcpy_s(value,
				_value->Length,
				(char *)(void *)Marshal::StringToHGlobalAnsi(_value),
				_value->Length);
			_value = Marshal::PtrToStringAnsi((IntPtr)(char *)value);
#if ENABLE_LOG
			DutFrame::Log->Info(String::Format("->dutId={0}, opType={1}, cfgType={2}, key={3}, value={4}, valueSize={5}, elemIndex={6}",
				dutId, wtOperateType, wtCfgType, _key, _value, valueSize, elemIndex));
#endif
			return true;
		}
		catch (Exception^ e)
		{
			LogUtils::UiDebug->Error(e->ToString());
		}
		return false;
	}
	return true;
}

int SignalData::GetBand()
{
	int band = 0;
	if (this->Freq > 3000)
	{
		band = 1;
	}

	return band;
}

String^ DutFrame::Char2String(char* data)
{
	return Marshal::PtrToStringAnsi((IntPtr)data);
}

char* DutFrame::String2Char(String^ data)
{
	return (char*)(void*)Marshal::StringToHGlobalAnsi(data);
}

DutFrame::DutFrame(String^ filename)
{
	this->WtSetUpDic = gcnew Dictionary<String^, Dictionary<String^, KeyValue^>^>;

	char* _filename = (char*)(void*)Marshal::StringToHGlobalAnsi(filename);
	hmodule = LoadLibrary(_filename);
	Marshal::FreeHGlobal(IntPtr(_filename));
	if (hmodule == NULL)
	{
		throw gcnew Exception("load plugin fail");
	}

	createPlugin = (create_plugin)GetProcAddress(hmodule, "CreatePlugin");
	destroyPlugin = (destroy_plugin)GetProcAddress(hmodule, "DestroyPlugin");
	getPluginVersion = (get_plugin_version)GetProcAddress(hmodule, "GetPluginVersion");

	IDut* dut = (IDut*)createPlugin();
	handleDut = dut;
}

String^ DutFrame::GetPluginVersion()
{
	char version[64] = { 0 };
	int verSize = 64;
	getPluginVersion(version, verSize);
	String^ strVersion = Marshal::PtrToStringAnsi((IntPtr)version);
	LogUtils::UiDebug->InfoFormat("getPluginVersion({0})", strVersion);
	return strVersion;
}

void DutFrame::DestroyPlugin()
{
	destroyPlugin(handleDut);
}

void DutFrame::SetCallBack()
{
	IDut* dut = (IDut*)handleDut;
	CallBackManager cbManager;
	cbManager.isStopRunning = CallBackIsStopRunning;
	cbManager.printLog = CallBackPrintLog;
	cbManager.cfgElementOperation = CallBackCfgElementOperation;
	cbManager.cfgArrayElementOperation = CallBackCfgArrayElementOperation;
	dut->SetCallBackManager(cbManager);
}

void DutFrame::SetDutId(int id)
{
	IDut* dut = (IDut*)handleDut;
	dut->SetDutId(id);
}


void DutFrame::Init()
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->Init();
	LogUtils::UiDebug->InfoFormat("{0} dut->Init()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->Init fail");
	}
}

bool DutFrame::IsDutReady()
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->IsDutReady();
	LogUtils::UiDebug->InfoFormat("{0} dut->IsDutReady()", ret);
	return ret;
}

void DutFrame::Open(WtDut wtDut)
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->Open((int)wtDut);
	LogUtils::UiDebug->InfoFormat("{0} dut->Open({1})", ret, wtDut);
	if (!ret)
	{
		throw gcnew Exception("dut->Open fail");
	}
}

void DutFrame::Close(WtDut wtDut)
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->Close((int)wtDut);
	LogUtils::UiDebug->InfoFormat("{0} dut->Close({1})", ret, wtDut);
	if (!ret)
	{
		throw gcnew Exception("dut->Close fail");
	}
}

void DutFrame::CalBegin(WtDut wtDut)
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->CalBegin((int)wtDut);
	LogUtils::UiDebug->InfoFormat("{0} dut->CalBegin({1})", ret, wtDut);
	if (!ret)
	{
		throw gcnew Exception("dut->CalBegin fail");
	}
}

void DutFrame::CalEnd(WtDut wtDut)
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->CalEnd((int)wtDut);
	LogUtils::UiDebug->InfoFormat("{0} dut->CalEnd({1})", ret, wtDut);
	if (!ret)
	{
		throw gcnew Exception("dut->CalEnd fail");
	}
}

void DutFrame::SaveCalData(WtDut wtDut)
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->SaveCalData((int)wtDut);
	LogUtils::UiDebug->InfoFormat("{0} dut->SaveCalData({1})", ret, wtDut);
	if (!ret)
	{
		throw gcnew Exception("dut->CalEnd fail");
	}
}

void DutFrame::SetSignal(SignalData^ signalData)
{
	Signal* signal = Convert2Signal(signalData);

	IDut* dut = (IDut*)handleDut;
	bool ret = dut->SetSignal((Signal *)signal);
	// TODO ToString()
	LogUtils::UiDebug->InfoFormat("{0} dut->SetSignal()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->SetSignal fail");
	}
}

int DutFrame::GetAntCount(int band)
{
	IDut* dut = (IDut*)handleDut;
	int ret = dut->GetAntCount(band);
	LogUtils::UiDebug->InfoFormat("{0} dut->GetAntCount({1})", ret, band);
	return ret;
}

void DutFrame::TxFrame(WtTxMode txMode)
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->TxFrame((int)txMode);
	LogUtils::UiDebug->InfoFormat("{0} dut->TxFrame({1})", ret, txMode);
	if (!ret)
	{
		throw gcnew Exception("dut->TxFrame fail");
	}
}

void DutFrame::TxStop()
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->TxStop();
	LogUtils::UiDebug->InfoFormat("{0} dut->TxStop()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->TxStop fail");
	}
}

void DutFrame::GetTgtPwrAndPwrReg(SignalData^ signalData)
{
	Signal* signal = Convert2Signal(signalData);
	IDut* dut = (IDut*)handleDut;
	int regVal;
	double targetPow = 0;
	regVal = this->PowerRegVal;
	bool ret = dut->GetTgtPwrAndPwrReg(signal, &targetPow, &regVal);
	this->PowerRegVal = regVal;
	LogUtils::UiDebug->InfoFormat("{0} dut->GetTgtPwrAndPwrReg({1}, {2}, {3})", ret, nullptr, targetPow, regVal);
	if (!ret)
	{
		throw gcnew Exception("dut->GetTgtPwrAndPwrReg fail");
	}
}

void DutFrame::GetTargetPowerAndReg(SignalData^ signalData, StringBuilder^ targetPow, StringBuilder^ regVal)
{
	Signal* signal = Convert2Signal(signalData);
	IDut* dut = (IDut*)handleDut;
	int _regVal;
	double _targetPow = 0;
	bool ret = dut->GetTgtPwrAndPwrReg(signal, &_targetPow, &_regVal);
	LogUtils::UiDebug->InfoFormat("{0} dut->GetTgtPwrAndPwrReg({1}, {2}, {3})", ret, nullptr, targetPow, regVal);
	if (!ret)
	{
		throw gcnew Exception("dut->GetTgtPwrAndPwrReg fail");
	}
	
	targetPow->Clear();
	targetPow->Append(_targetPow);
	regVal->Clear();
	regVal->Append(_regVal);
}

void DutFrame::AdjustFreqReg(double freqErrPpm)
{
	IDut* dut = (IDut*)handleDut;
	int regVal;
	regVal = this->FreqRegVal;
	bool ret = dut->AdjustFreqReg(freqErrPpm, &regVal);
	this->FreqRegVal = regVal;
	LogUtils::UiDebug->InfoFormat("{0} dut->AdjustFreqReg({1}, {2})", ret, freqErrPpm, this->FreqRegVal);
	if (!ret)
	{
		throw gcnew Exception("dut->AdjustFreqReg fail");
	}
}

void DutFrame::AdjustPowerReg(double powerErr)
{
	IDut* dut = (IDut*)handleDut;
	int regVal;
	regVal = this->PowerRegVal;
	bool ret = dut->AdjustPwrReg(powerErr, &regVal);
	this->PowerRegVal = regVal;
	LogUtils::UiDebug->InfoFormat("{0} dut->AdjustPowerReg({1}, {2})", ret, powerErr, this->PowerRegVal);
	if (!ret)
	{
		throw gcnew Exception("dut->AdjustPwrReg fail");
	}
}

bool DutFrame::SetFreqCalRegVal(int band, int regVal)
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->SetFreqCalRegVal(band, regVal);
	LogUtils::UiDebug->InfoFormat("{0} dut->SetFreqCalRegVal({1}, {2})", ret, band, regVal);
	return ret;
}

bool DutFrame::SetPwrCalRegVal(int band, int ant, int channel, int regVal)
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->SetPwrCalRegVal(band, ant, channel, &regVal);
	LogUtils::UiDebug->InfoFormat("{0} dut->SetPwrCalRegVal({1}, {2}, {3}, {4})", ret, band, ant, channel, regVal);
	return ret;
}

void DutFrame::RxStart()
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->RxStart();
	LogUtils::UiDebug->InfoFormat("{0} dut->RxStart()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->RxStart fail");
	}
}

void DutFrame::RxStop()
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->RxStop();
	LogUtils::UiDebug->InfoFormat("{0} dut->RxStop()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->RxStop fail");
	}
}

void DutFrame::GetRxResult(RxResult^ rxResult)
{
	IDut* dut = (IDut*)handleDut;
	stRxResult result;
	bool ret = dut->GetPerResult(&result);
	LogUtils::UiDebug->InfoFormat("{0} dut->GetPerResult()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->GetPerResult fail");
	}

	rxResult->Ber = result.ber;
	rxResult->BitCnt = result.bitCnt;
	rxResult->Rssi = result.rssi;
	rxResult->FrameCnt = result.frameCnt;
}

void DutFrame::TempratureCompensation()
{
	IDut* dut = (IDut*)handleDut;
	int type = 0;
	bool ret = dut->TempCompensation(type);
	LogUtils::UiDebug->InfoFormat("{0} dut->TempCompensation()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->TempCompensation fail");
	}
}

void DutFrame::SetMac(WtMacType wtMacType, String^ mac)
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->SetMac((int)wtMacType, this->String2Char(mac));
	LogUtils::UiDebug->InfoFormat("{0} dut->SetMac()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->SetMac fail");
	}
}

void DutFrame::GetMac(WtMacType wtMacType, StringBuilder^ mac)
{
	IDut* dut = (IDut*)handleDut;
	char _mac[64] = { 0 };
	bool ret = dut->GetMac(_mac, 64, (int)wtMacType);
	LogUtils::UiDebug->InfoFormat("{0} dut->GetMac()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->GetMac fail");
	}

	mac->Clear();
	mac->Append(this->Char2String(_mac));
}

void DutFrame::SaveCalData()
{
	IDut* dut = (IDut*)handleDut;
	int type = 0;
	bool ret = dut->SaveCalData(type);
	LogUtils::UiDebug->InfoFormat("{0} dut->SaveCalData()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->SaveCalData fail");
	}
}

void DutFrame::WriteEfuse(WtDut wtDut)
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->WriteEfuse((int)wtDut);
	LogUtils::UiDebug->InfoFormat("{0} dut->WriteEfuse()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->WriteEfuse fail");
	}
}

void DutFrame::CheckEfuse(WtDut wtDut)
{
	IDut* dut = (IDut*)handleDut;
	bool ret = dut->CheckEfuse((int)wtDut);
	LogUtils::UiDebug->InfoFormat("{0} dut->CheckEfuse()", ret);
	if (!ret)
	{
		throw gcnew Exception("dut->CheckEfuse fail");
	}
}