#pragma once

#include "Wlan.h"

using namespace System;
using namespace AILinkFactoryAuto::Task::Executer;
using namespace AILinkFactoryAuto::Task::Property;
using namespace AILinkFactoryAuto::Task::Wlan::Utils;
using namespace AILinkFactoryAuto::Instrument::WtApi;

namespace AILinkFactoryAuto {
	namespace Task
	{
		namespace Wlan
		{
			namespace Executer
			{
				public ref class RxVerifyWifiExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};
			}

			namespace Property
			{
				public ref class RxVerifyWifiProperties : CommonProperties
				{
				public:
					RxVerifyWifiProperties();

					[Category("Common"), Description("power")]
					property int Power;

					[Category("Common"), Description("freq, unit: MHz")]
					property double Freq;

					[Category("Common"), Description("demod")]
					property WtDemo Demod;

					[Category("Common"), Description("antenna")]
					property WtChain Antenna;

					[Category("Common"), Description("bw")]
					property WtBw WtBw;

					[Category("Common"), Description("mcs")]
					property WtMcs WtMcs;

					[Category("Common"), Description("gi")]
					property WtGi WtGi;

					[Category("Common"), Description("preamble")]
					property int Preamble;

					[Category("Common"), Description("port")]
					property WtPort Port;

					[Category("Common"), Description("loss")]
					property double Loss;

					[Category("Common"), Description("delay verify ms")]
					property int DelayVerify;

					[Category("Common"), Description("number of packets")]
					property int NumberPackets;

					[Category("Result"), Description("limit of number of packets"), TypeConverter(LimitConverter::typeid)]
					property LimitProperties^ LimitNumberPackets;
				};
			}
		}
	}
}