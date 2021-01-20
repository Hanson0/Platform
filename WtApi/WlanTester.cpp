// 这是主 DLL 文件。

#include "stdafx.h"
#include "WtErrCode.h"
#include "WtPort.h"
#include "WtSignal.h"
#include "WlanTester.h"
#include "tester.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace AILinkFactoryAuto::Instrument::WtApi;
using namespace AILinkFactoryAuto::Utils;

String^ WlanTester::Char2String(char* data)
{
	return Marshal::PtrToStringAnsi((IntPtr)data);
}

char* WlanTester::String2Char(String^ data)
{
	return (char*)(void*)Marshal::StringToHGlobalAnsi(data);
}

void WlanTester::WtDllInitialize()
{
	static bool isFirst = true;
	if (isFirst)
	{
		isFirst = false;
		WT_DLLInitialize();
	}
}

void WlanTester::WtDllTerminate()
{
	static bool isFirst = true;
	if (isFirst)
	{
		isFirst = false;
		WT_DLLTerminate();
	}
}

void WlanTester::WtConnect(String^ ipAddr)
{

	char* _ipAddr = String2Char(ipAddr);
	int _connID = -1;
	int ret = WT_Connect(_ipAddr, &_connID);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_Connect({1}, {2})", wtErrCode, ipAddr, this->connID);
	this->connID = _connID;
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_Connect fail");
	}
}

void WlanTester::WtForceConnect(String^ ipAddr)
{
	char* _ipAddr = String2Char(ipAddr);
	int _connID = -1;
	int ret = WT_ForceConnect(_ipAddr, &_connID);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_ForceConnect({1}, {2})", wtErrCode, ipAddr, this->connID);
	this->connID = _connID;
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_ForceConnect fail");
	}
}

void WlanTester::WtDisConnect()
{
	WT_DisConnect(this->connID);
	LogUtils::UiDebug->DebugFormat("WT_DisConnect({0})", this->connID);
}

WtInfo^ WlanTester::WtGetTesterVersion()
{
	TesterInfo testInfo;
	int bufferSize = 512;
	int testerType = -1;
	int ret = WT_GetTesterVersion(this->connID, &testInfo, bufferSize, &testerType);
	WtInfo^ wtInfo = gcnew WtInfo();
	wtInfo->Ip = Char2String(testInfo.ip);
	wtInfo->SubMask = Char2String(testInfo.SubMask);
	wtInfo->GateAddr = Char2String(testInfo.GateAddr);
	wtInfo->Sn = Char2String(testInfo.SN);
	wtInfo->Name = Char2String(testInfo.name);
	wtInfo->MacAddr = Char2String(testInfo.MacAddr);
	wtInfo->FwVersion = Char2String(testInfo.FW_Version);
	wtInfo->HwVersion = Char2String(testInfo.HW_Version);
	wtInfo->RfVersion = Char2String(testInfo.RF_Version);
	wtInfo->CalDate = Char2String(testInfo.cal_date);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_GetTesterVersion({1}, {2}, {3}, {4})", wtErrCode, this->connID, wtInfo, bufferSize, testerType);
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_GetTesterVersion fail");
	}

	return wtInfo;
}

void WlanTester::WtSetExternalGain(double extGain)
{
	int ret = WT_SetExternalGain(this->connID, extGain);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_SetExternalGain({1}, {2}})", ret, this->connID, extGain);
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_SetExternalGain fail");
	}
}

void WlanTester::WtGetDefaultParameter()
{
	VsaParameter vsaParameter;
	VsgParameter vsgParameter;

	int ret = WT_GetDefaultParameter(&vsaParameter, &vsgParameter);

	this->WtVsaInfo = gcnew WtVsaParameter();
	this->WtVsaInfo->Freq = vsaParameter.freq;
	this->WtVsaInfo->MaxPower = vsaParameter.max_power;
	this->WtVsaInfo->SmpTime = vsaParameter.smp_time;
	this->WtVsaInfo->RfPort = (WtPort)vsaParameter.rfPort;
	this->WtVsaInfo->TrigType = (WtTrigType)vsaParameter.trig_type;
	this->WtVsaInfo->TrigLevel = vsaParameter.trig_level;
	this->WtVsaInfo->TrigTimeout = vsaParameter.trig_timeout;
	this->WtVsaInfo->TrigPretime = vsaParameter.trig_pretime;
	this->WtVsaInfo->Demod = (WtDemo)vsaParameter.demod;
	this->WtVsaInfo->IqSwap = (WtIqSwap)vsaParameter.iq_swap;
	this->WtVsaInfo->PhCorr = vsaParameter.ph_corr;
	this->WtVsaInfo->ChEstimate = vsaParameter.ch_estimate;
	this->WtVsaInfo->SymTimCorr = vsaParameter.sym_tim_corr;
	this->WtVsaInfo->FreqSync = vsaParameter.freq_sync;
	this->WtVsaInfo->AmplTrack = vsaParameter.ampl_track;
	this->WtVsaInfo->EvmMethod11b = vsaParameter.evm_method_11b;
	this->WtVsaInfo->DcRemoval = vsaParameter.dc_removal;
	this->WtVsaInfo->EqTaps = vsaParameter.eq_taps;
	this->WtVsaInfo->CckPhCorr = vsaParameter.cck_ph_corr;
	this->WtVsaInfo->BtRate = vsaParameter.bt_Rate;
	this->WtVsaInfo->BtPacketType = vsaParameter.bt_packet_type;
	this->WtVsaInfo->TimeoutWaiting = vsaParameter.TimeoutWaiting;

	this->WtVsgInfo = gcnew WtVsgParameter();
	this->WtVsgInfo->Freq = vsgParameter.freq;
	this->WtVsgInfo->Power = vsgParameter.power;
	this->WtVsgInfo->RfPort = (WtPort)vsgParameter.rfPort;
	this->WtVsgInfo->WaveType = (WtSignal)vsgParameter.waveType;
	this->WtVsgInfo->Wave = this->Char2String(vsgParameter.wave);
	this->WtVsgInfo->Repeat = vsgParameter.repeat;
	this->WtVsgInfo->WaveGap = vsgParameter.wave_gap;
	this->WtVsgInfo->TimeoutWaiting = vsaParameter.TimeoutWaiting;

	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_GetDefaultParameter({1}, {2})", ret, this->WtVsaInfo->ToString(), this->WtVsgInfo->ToString());
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_GetDefaultParameter fail");
	}
}

void WlanTester::WtSetVsa()
{
	VsaParameter vsaParameter;
	vsaParameter.freq = this->WtVsaInfo->Freq;
	vsaParameter.max_power = this->WtVsaInfo->MaxPower;
	vsaParameter.smp_time = this->WtVsaInfo->SmpTime;
	vsaParameter.rfPort = (int)this->WtVsaInfo->RfPort;
	vsaParameter.trig_type = (int)this->WtVsaInfo->TrigType;
	vsaParameter.trig_level = this->WtVsaInfo->TrigLevel;
	vsaParameter.trig_timeout = this->WtVsaInfo->TrigTimeout;
	vsaParameter.trig_pretime = this->WtVsaInfo->TrigPretime;
	vsaParameter.demod = (int)this->WtVsaInfo->Demod;
	vsaParameter.iq_swap = (int)this->WtVsaInfo->IqSwap;
	vsaParameter.ph_corr = this->WtVsaInfo->PhCorr;
	vsaParameter.ch_estimate = this->WtVsaInfo->ChEstimate;
	vsaParameter.sym_tim_corr = this->WtVsaInfo->SymTimCorr;
	vsaParameter.freq_sync = this->WtVsaInfo->FreqSync;
	vsaParameter.ampl_track = this->WtVsaInfo->AmplTrack;
	vsaParameter.evm_method_11b = this->WtVsaInfo->EvmMethod11b;
	vsaParameter.dc_removal = this->WtVsaInfo->DcRemoval;
	vsaParameter.eq_taps = this->WtVsaInfo->EqTaps;
	vsaParameter.cck_ph_corr = this->WtVsaInfo->CckPhCorr;
	vsaParameter.bt_Rate = this->WtVsaInfo->BtRate;
	vsaParameter.bt_packet_type = this->WtVsaInfo->BtPacketType;
	vsaParameter.TimeoutWaiting = this->WtVsaInfo->TimeoutWaiting;
	int ret = WT_SetVSA(this->connID, &vsaParameter);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_SetVSA({1}, {2})", wtErrCode, this->connID, this->WtVsaInfo);
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_SetVSA fail");
	}
}

void WlanTester::WtSetVsg()
{
	VsgParameter vsgParameter;
	vsgParameter.freq = this->WtVsgInfo->Freq;
	vsgParameter.power = this->WtVsgInfo->Power;
	vsgParameter.repeat = this->WtVsgInfo->Repeat;
	vsgParameter.rfPort = (int)this->WtVsgInfo->RfPort;
	vsgParameter.TimeoutWaiting = this->WtVsgInfo->TimeoutWaiting;
	vsgParameter.wave = this->String2Char(this->WtVsgInfo->Wave);
	vsgParameter.waveType = (int)this->WtVsgInfo->WaveType;
	vsgParameter.wave_gap = this->WtVsgInfo->WaveGap;
	int ret = WT_SetVSG(this->connID, &vsgParameter);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_SetVSG({1}, {2})", wtErrCode, this->connID, this->WtVsgInfo);
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_SetVSG fail");
	}
}

void WlanTester::WtDataCapture()
{
	int ret = WT_DataCapture(this->connID);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_DataCapture({1})", wtErrCode, this->connID);
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_DataCapture fail");
	}
}

void WlanTester::WtSetVsaAutoRange()
{
	VsaParameter vsaParameter;
	vsaParameter.freq = this->WtVsaInfo->Freq;
	vsaParameter.max_power = this->WtVsaInfo->MaxPower;
	vsaParameter.smp_time = this->WtVsaInfo->SmpTime;
	vsaParameter.rfPort = (int)this->WtVsaInfo->RfPort;
	vsaParameter.trig_type = (int)this->WtVsaInfo->TrigType;
	vsaParameter.trig_level = this->WtVsaInfo->TrigLevel;
	vsaParameter.trig_timeout = this->WtVsaInfo->TrigTimeout;
	vsaParameter.trig_pretime = this->WtVsaInfo->TrigPretime;
	vsaParameter.demod = (int)this->WtVsaInfo->Demod;
	vsaParameter.iq_swap = (int)this->WtVsaInfo->IqSwap;
	vsaParameter.ph_corr = this->WtVsaInfo->PhCorr;
	vsaParameter.ch_estimate = this->WtVsaInfo->ChEstimate;
	vsaParameter.sym_tim_corr = this->WtVsaInfo->SymTimCorr;
	vsaParameter.freq_sync = this->WtVsaInfo->FreqSync;
	vsaParameter.ampl_track = this->WtVsaInfo->AmplTrack;
	vsaParameter.evm_method_11b = this->WtVsaInfo->EvmMethod11b;
	vsaParameter.dc_removal = this->WtVsaInfo->DcRemoval;
	vsaParameter.eq_taps = this->WtVsaInfo->EqTaps;
	vsaParameter.cck_ph_corr = this->WtVsaInfo->CckPhCorr;
	vsaParameter.bt_Rate = this->WtVsaInfo->BtRate;
	vsaParameter.bt_packet_type = this->WtVsaInfo->BtPacketType;
	vsaParameter.TimeoutWaiting = this->WtVsaInfo->TimeoutWaiting;
	int ret = WT_SetVSA_AutoRange(this->connID, &vsaParameter);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_SetVSA_AutoRange({1})", wtErrCode, this->connID);
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_SetVSA_AutoRange fail");
	}
}

void WlanTester::WtStopDataCapture()
{
	int ret = WT_StopDataCapture(this->connID);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_StopDataCapture({1})", wtErrCode, this->connID);
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_StopDataCapture fail");
	}
}

void WlanTester::WtGetResult(WtResult^ wtResult)
{
	char *anaParamString = this->String2Char(wtResult->AnaParamString);
	double result = 0; 
	char description[256] = { 0 }; 
	char unit[256] = { 0 };
	int ret = WT_GetResult(this->connID, anaParamString, &result, description, unit);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_GetResult({1})", wtErrCode, this->connID, wtResult);
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_GetResult fail");
	}

	wtResult->Result = result;
	wtResult->Description = this->Char2String(description);
	wtResult->Unit = this->Char2String(unit);
}

void WlanTester::WtStartVsg()
{
	int ret = WT_StartVSG(this->connID);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_StartVSG({1})", wtErrCode, this->connID);
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_StartVSG fail");
	}
}

void WlanTester::WtStopVsg()
{
	int ret = WT_StopVSG(this->connID);
	WtErrCode wtErrCode = (WtErrCode)ret;
	LogUtils::UiDebug->DebugFormat("{0} WT_StopVSG({1})", wtErrCode, this->connID);
	if (wtErrCode != WtErrCode::WT_ERR_CODE_OK)
	{
		throw gcnew Exception("WT_StopVSG fail");
	}
}