// 这是主 DLL 文件。

#include "stdafx.h"

#include "FreqCal.h"
#include "CalProperties.h"

#define INIT_FREQ_CAL_PPM 10000 

using namespace System::Threading;
using namespace AILinkFactoryAuto::Task::Wlan::Executer;
using namespace AILinkFactoryAuto::Task::Wlan::Property;
using namespace AILinkFactoryAuto::Task;
using namespace AILinkFactoryAuto::Utils;
using namespace AILinkFactoryAuto::Core;
using namespace AILinkFactoryAuto::Task::Property;
using namespace AILinkFactoryAuto::Task::Executer;
using namespace AILinkFactoryAuto::Task::Wlan::Utils;
using namespace AILinkFactoryAuto::Instrument::WtApi;

void FreqCalExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	CalProperties^ config = (CalProperties^)properties;
	ILog^ log = globalDic->Get<ILog^>();
	WlanTester^ wlanTester = globalDic->Get<WlanTester^>();
	DutFrame^ dutFrame = globalDic->Get<DutFrame^>();

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
		dutFrame->TxFrame(WtTxMode::TX_MODE_FREQ_CAL);

		Thread::Sleep(config->DelayCal);

		dutFrame->AdjustFreqReg(INIT_FREQ_CAL_PPM);
		bool ret = false;
		for (int i = 0; i < config->RetryCountCal; i++)
		{
			try
			{
				wlanTester->WtSetExternalGain(-1 * config->Loss);

				wlanTester->WtGetDefaultParameter();
				wlanTester->WtVsaInfo->Freq = config->Freq * (double)(1e6);
				wlanTester->WtVsaInfo->RfPort = config->Port;
				wlanTester->WtVsaInfo->TrigType = WtTrigType::WT_TRIG_TYPE_IF;
				wlanTester->WtVsaInfo->MaxPower = config->Power + 12 - config->Loss;
				wlanTester->WtVsaInfo->Demod = config->Demod;
				wlanTester->WtSetVsa();

				wlanTester->WtDataCapture();
				WtResult^ wtResult = gcnew WtResult();
				wtResult->AnaParamString = WtResParamString::WT_RES_FRAME_FREQ_ERR;
				wlanTester->WtGetResult(wtResult);

				double freqErrorPpm = (wtResult->Result / (config->Freq * 1e6)) * 1e6;
				log->Info(String::Format("FreqRegVal={0}, FreqErrorPpm={1}", dutFrame->FreqRegVal, freqErrorPpm));

				wtResult->AnaParamString = WtResParamString::WT_RES_POWER_FRAME_DB;
				wlanTester->WtGetResult(wtResult);
				double power = wtResult->Result;
				log->Info(String::Format("Power={0}", power));

				if (freqErrorPpm >= config->LimitMin && freqErrorPpm <= config->LimitMax)
				{
					if (dutFrame->SetFreqCalRegVal(band, dutFrame->FreqRegVal))
					{
						ret = true;
					}
					break;
				}

				Thread::Sleep(config->DelayCal);
				dutFrame->AdjustFreqReg(freqErrorPpm);
			}
			catch (Exception^ e)
			{
				log->Fail(e->Message);
			}
		}
		if (!ret)
		{
			throw gcnew Exception("freq cal fail");
		}
	}
	catch (Exception^ e)
	{
		throw e;
	}
	finally 
	{
		dutFrame->TxStop();
	}
}