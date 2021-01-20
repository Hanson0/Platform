#pragma once

#include "Wlan.h"

using namespace System;
using namespace AILinkFactoryAuto::Task;
using namespace AILinkFactoryAuto::Task::Executer;
using namespace AILinkFactoryAuto::Task::Property;
using namespace AILinkFactoryAuto::Task::Wlan::Utils;
using namespace AILinkFactoryAuto::Instrument::WtApi;

namespace AILinkFactoryAuto {
	namespace Task
	{
		namespace Wlan
		{
			namespace Property
			{
				public ref class CalProperties : CommonProperties
				{
				public:
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

					[Category("Common"), Description("delay cal ms")]
					property int DelayCal;

					[Category("Common"), Description("retry count cal")]
					property int RetryCountCal;

					[Category("Common"), Description("limit min")]
					property double LimitMin;

					[Category("Common"), Description("limit max")]
					property double LimitMax;
				};
			}
		}
	}
}