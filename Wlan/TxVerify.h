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
				public ref class TxVerifyWifiExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class TxVerifyBtExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};
			}

			namespace Property
			{
				public ref class TxVerifyWifiProperties : CommonProperties
				{
				public:
					TxVerifyWifiProperties();

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

					[Category("Result"), Description("power"), TypeConverter(LimitConverter::typeid)]
					property LimitProperties^ LimitPower;

					[Category("Result"), Description("evm"), TypeConverter(LimitConverter::typeid)]
					property LimitProperties^ LimitEvm;

					[Category("Result"), Description("freq err"), TypeConverter(LimitConverter::typeid)]
					property LimitProperties^ LimitFreqErr;

					[Category("Result"), Description("mask err"), TypeConverter(LimitConverter::typeid)]
					property LimitProperties^ LimitMaskErr;
				};


				public ref class TxVerifyBtProperties : CommonProperties
				{
				public:
					TxVerifyBtProperties();
			
				};
			}
		}
	}
}