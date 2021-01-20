// 这是主 DLL 文件。

#include "stdafx.h"

#include "RxVerify.h"

using namespace System::Text;
using namespace System::Threading;
using namespace AILinkFactoryAuto::Task::Wlan::Executer;
using namespace AILinkFactoryAuto::Task::Wlan::Property;
using namespace AILinkFactoryAuto::Task;
using namespace AILinkFactoryAuto::Core;
using namespace AILinkFactoryAuto::Task::Property;
using namespace AILinkFactoryAuto::Task::Executer;
using namespace AILinkFactoryAuto::Common;

RxVerifyWifiProperties::RxVerifyWifiProperties()
{
	this->LimitNumberPackets = gcnew LimitProperties();
	this->LimitNumberPackets->Name = "NumberPackets";
	this->LimitNumberPackets->Unit = "";
}

void RxVerifyWifiExecuter::Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic)
{
	RxVerifyWifiProperties^ config = (RxVerifyWifiProperties^)properties;
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

	try
	{
		int band = signalData->GetBand();

		int antCount = dutFrame->GetAntCount(band);
		dutFrame->SetSignal(signalData);
		dutFrame->RxStart();

		wlanTester->WtGetDefaultParameter();
		wlanTester->WtVsgInfo->Freq = config->Freq * (double)(1e6);
		wlanTester->WtVsgInfo->RfPort = config->Port;

		String^ wave;
		switch (config->Demod)
		{
		case WtDemo::WT_DEMOD_11B:
			if (config->WtMcs == WtMcs::MCS_1M)
			{
				wave = "./wave\\120M\\1 Mbps(DSSS).bwv";
			}
			else if (config->WtMcs == WtMcs::MCS_2M)
			{
				wave = "./wave\\120M\\2 Mbps(DSSS).bwv";
			}
			else if (config->WtMcs == WtMcs::MCS_5_5M)
			{
				wave = "./wave\\120M\\5.5 Mbps(DSSS).bwv";
			}
			else if (config->WtMcs == WtMcs::MCS_11M)
			{
				wave = "./wave\\120M\\11 Mbps(DSSS).bwv";
			}
			break;

		case WtDemo::WT_DEMOD_11AG:
			if (config->WtMcs == WtMcs::MCS_6M)
			{
				wave = "./wave\\120M\\6 Mbps(OFDM).bwv";
			}
			if (config->WtMcs == WtMcs::MCS_9M)
			{
				wave = "./wave\\120M\\9 Mbps(OFDM).bwv";
			}
			if (config->WtMcs == WtMcs::MCS_12M)
			{
				wave = "./wave\\120M\\12 Mbps(OFDM).bwv";
			}
			if (config->WtMcs == WtMcs::MCS_18M)
			{
				wave = "./wave\\120M\\18 Mbps(OFDM).bwv";
			}
			if (config->WtMcs == WtMcs::MCS_24M)
			{
				wave = "./wave\\120M\\24 Mbps(OFDM).bwv";
			}
			if (config->WtMcs == WtMcs::MCS_36M)
			{
				wave = "./wave\\120M\\36 Mbps(OFDM).bwv";
			}
			if (config->WtMcs == WtMcs::MCS_48M)
			{
				wave = "./wave\\120M\\48 Mbps(OFDM).bwv";
			}
			if (config->WtMcs == WtMcs::MCS_54M)
			{
				wave = "./wave\\120M\\54 Mbps(OFDM).bwv";
			}
			break;

		case WtDemo::WT_DEMOD_11N_20M:
			wave = "./wave\\120M\\" + "HT20-" + config->WtMcs.ToString() + ".bwv";
			break;

		case WtDemo::WT_DEMOD_11N_40M:
			wave = "./wave\\120M\\" + "HT40-" + config->WtMcs.ToString() + ".bwv";
			break;

		case WtDemo::WT_DEMOD_11AC_20M:
			wave = "./wave\\120M\\" + "VHT20-" + config->WtMcs.ToString() + ".bwv";
			break;

		case WtDemo::WT_DEMOD_11AC_40M:
			wave = "./wave\\120M\\" + "VHT40-" + config->WtMcs.ToString() + ".bwv";
			break;

		case WtDemo::WT_DEMOD_11AC_80M:
			wave = "./wave\\120M\\" + "VHT80-" + config->WtMcs.ToString() + ".bwv";
			break;

		default:
			break;
		}

		wlanTester->WtVsgInfo->Wave = wave;
		wlanTester->WtVsgInfo->WaveType = WtSignal::SIG_USERFILE;
		wlanTester->WtVsgInfo->Repeat = config->NumberPackets;
		wlanTester->WtSetVsg();
		wlanTester->WtStartVsg();
		Thread::Sleep(config->DelayVerify);

		RxResult^ rxResult = gcnew RxResult();
		dutFrame->GetRxResult(rxResult);

		bool result = true;
		if (config->LimitNumberPackets->Enable)
		{
			if (limit->CheckDouble(rxResult->FrameCnt, config->LimitNumberPackets))
			{
				result = false;
			}
		}

		if (!result)
		{
			throw gcnew BaseException("rx verify fail");
		}
	}
	finally 
	{
		try
		{
			wlanTester->WtStopVsg();
		}
		catch (Exception^)
		{

		}
		try
		{
			dutFrame->RxStop();
		}
		catch (Exception^)
		{

		}
	}
}