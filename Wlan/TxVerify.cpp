// 这是主 DLL 文件。

#include "stdafx.h"

#include "TxVerify.h"

using namespace System::Text;
using namespace System::Threading;
using namespace AILinkFactoryAuto::Task::Wlan::Executer;
using namespace AILinkFactoryAuto::Task::Wlan::Property;
using namespace AILinkFactoryAuto::Task;
using namespace AILinkFactoryAuto::Core;
using namespace AILinkFactoryAuto::Task::Property;
using namespace AILinkFactoryAuto::Task::Executer;
using namespace AILinkFactoryAuto::Common;

TxVerifyWifiProperties::TxVerifyWifiProperties()
{
	this->LimitPower = gcnew LimitProperties();
	this->LimitPower->Name = "Power";
	this->LimitPower->Unit = "dBm";

	this->LimitEvm = gcnew LimitProperties();
	this->LimitEvm->Name = "EVM";
	this->LimitEvm->Unit = "dB";

	this->LimitFreqErr = gcnew LimitProperties();
	this->LimitFreqErr->Name = "FreqErr";
	this->LimitFreqErr->Unit = "ppm";

	this->LimitMaskErr = gcnew LimitProperties();
	this->LimitMaskErr->Name = "MaskErr";
	this->LimitMaskErr->Unit = "%";
}

void TxVerifyWifiExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	TxVerifyWifiProperties^ config = (TxVerifyWifiProperties^)properties;
	ILog^ log = globalDic->Get<ILog^>();
	WlanTester^ wlanTester = globalDic->Get<WlanTester^>();
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	Limit^ limit = globalDic->Get<Limit^>();

	SignalData^ signalData = gcnew SignalData();
	signalData->Pow = config->Power;
	signalData->Freq = config->Freq * 10e6;
	signalData->WtBw = config->WtBw;
	signalData->WtDemodPlugin = (WtDemodPlugin)(int)config->Demod;
	signalData->Antenna = (int)config->Antenna;
	int msc = WtUtils::WtMcs2Int(config->WtMcs);
	signalData->Mcs = msc;
	signalData->WtGi = config->WtGi;
	signalData->Preamble = config->Preamble;

	int band = signalData->GetBand();

	try
	{
		int antCount = dutFrame->GetAntCount(band);

		dutFrame->SetSignal(signalData);
		dutFrame->GetTgtPwrAndPwrReg(signalData);
		//StringBuilder^ targetPower = gcnew StringBuilder();
		//StringBuilder^ regVal = gcnew StringBuilder();
		//dutFrame->GetTargetPowerAndReg(signalData, targetPower, regVal);

		dutFrame->TxFrame(WtTxMode::TX_MODE_TX_VERIFY);

		Thread::Sleep(config->DelayVerify);

		wlanTester->WtSetExternalGain(-1 * config->Loss);

		wlanTester->WtGetDefaultParameter();
		wlanTester->WtVsaInfo->Freq = config->Freq * (double)(1e6);
		wlanTester->WtVsaInfo->RfPort = config->Port;
		wlanTester->WtVsaInfo->TrigType = WtTrigType::WT_TRIG_TYPE_IF;
		wlanTester->WtVsaInfo->MaxPower = config->Power + 12;
		wlanTester->WtVsaInfo->Demod = config->Demod;
		wlanTester->WtSetVsa();

		wlanTester->WtDataCapture();

		WtResult^ wtResult = gcnew WtResult();

		bool result = true;
		if (config->LimitPower->Enable)
		{
			wtResult->AnaParamString = WtResParamString::WT_RES_POWER_FRAME_DB;
			wlanTester->WtGetResult(wtResult);
			if (!limit->CheckDouble(wtResult->Result, config->LimitPower))
			{
				result = false;
			}
		}

		if (config->LimitFreqErr->Enable)
		{
			wtResult->AnaParamString = WtResParamString::WT_RES_FRAME_FREQ_ERR;
			wlanTester->WtGetResult(wtResult);
			double freqErrorPpm = (wtResult->Result / (config->Freq * 1e6)) * 1e6;
			if (!limit->CheckDouble(freqErrorPpm, config->LimitFreqErr))
			{
				result = false;
			}
		}

		if (config->LimitEvm->Enable)
		{
			wtResult->AnaParamString = WtResParamString::WT_RES_FRAME_EVM_ALL;
			wlanTester->WtGetResult(wtResult);
			if (!limit->CheckDouble(wtResult->Result, config->LimitEvm))
			{
				result = false;
			}
		}

		if (config->LimitMaskErr->Enable)
		{
			wtResult->AnaParamString = WtResParamString::WT_RES_SPECTRUM_MASK_ERR_PERCENT;
			wlanTester->WtGetResult(wtResult);
			if (!limit->CheckDouble(wtResult->Result, config->LimitMaskErr))
			{
				result = false;
			}
		}

		if (!result)
		{
			throw gcnew BaseException("tx verify fail");
		}
	}
	finally
	{
		try
		{
			dutFrame->TxStop();
		}
		catch (Exception^)
		{

		}
	}
}

TxVerifyBtProperties::TxVerifyBtProperties()
{
}

void TxVerifyBtExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	TxVerifyWifiProperties^ config = (TxVerifyWifiProperties^)properties;
	ILog^ log = globalDic->Get<ILog^>();
	WlanTester^ wlanTester = globalDic->Get<WlanTester^>();
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();
	Limit^ limit = globalDic->Get<Limit^>();

	SignalData^ signalData = gcnew SignalData();
	signalData->Pow = config->Power;
	signalData->Freq = config->Freq * 10e6;
	signalData->WtBw = config->WtBw;
	signalData->WtDemodPlugin = (WtDemodPlugin)(int)config->Demod;
	signalData->Antenna = (int)config->Antenna;
	int msc = WtUtils::WtMcs2Int(config->WtMcs);
	signalData->Mcs = msc;
	signalData->WtGi = config->WtGi;
	signalData->Preamble = config->Preamble;

	int band = signalData->GetBand();

	try
	{
		int antCount = dutFrame->GetAntCount(band);

		dutFrame->SetSignal(signalData);
		dutFrame->GetTgtPwrAndPwrReg(signalData);
		//StringBuilder^ targetPower = gcnew StringBuilder();
		//StringBuilder^ regVal = gcnew StringBuilder();
		//dutFrame->GetTargetPowerAndReg(signalData, targetPower, regVal);

		dutFrame->TxFrame(WtTxMode::TX_MODE_TX_VERIFY);

		Thread::Sleep(config->DelayVerify);

		wlanTester->WtSetExternalGain(-1 * config->Loss);

		wlanTester->WtGetDefaultParameter();
		wlanTester->WtVsaInfo->Freq = config->Freq * (double)(1e6);
		wlanTester->WtVsaInfo->RfPort = config->Port;
		wlanTester->WtVsaInfo->TrigType = WtTrigType::WT_TRIG_TYPE_IF;
		wlanTester->WtVsaInfo->MaxPower = config->Power + 12;
		wlanTester->WtVsaInfo->Demod = config->Demod;
		wlanTester->WtSetVsa();

		wlanTester->WtDataCapture();

		WtResult^ wtResult = gcnew WtResult();

		bool result = true;
		if (config->LimitPower->Enable)
		{
			wtResult->AnaParamString = WtResParamString::WT_RES_POWER_FRAME_DB;
			wlanTester->WtGetResult(wtResult);
			if (!limit->CheckDouble(wtResult->Result, config->LimitPower))
			{
				result = false;
			}
		}

		if (config->LimitFreqErr->Enable)
		{
			wtResult->AnaParamString = WtResParamString::WT_RES_FRAME_FREQ_ERR;
			wlanTester->WtGetResult(wtResult);
			double freqErrorPpm = (wtResult->Result / (config->Freq * 1e6)) * 1e6;
			if (!limit->CheckDouble(freqErrorPpm, config->LimitFreqErr))
			{
				result = false;
			}
		}

		if (config->LimitEvm->Enable)
		{
			wtResult->AnaParamString = WtResParamString::WT_RES_FRAME_EVM_ALL;
			wlanTester->WtGetResult(wtResult);
			if (!limit->CheckDouble(wtResult->Result, config->LimitEvm))
			{
				result = false;
			}
		}

		if (config->LimitMaskErr->Enable)
		{
			wtResult->AnaParamString = WtResParamString::WT_RES_SPECTRUM_MASK_ERR_PERCENT;
			wlanTester->WtGetResult(wtResult);
			if (!limit->CheckDouble(wtResult->Result, config->LimitMaskErr))
			{
				result = false;
			}
		}

		if (!result)
		{
			throw gcnew BaseException("tx verify fail");
		}
	}
	finally
	{
		try
		{
			dutFrame->TxStop();
		}
		catch (Exception^)
		{

		}
	}
}