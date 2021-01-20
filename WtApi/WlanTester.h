// WtApi.h

#pragma once

#include "WtVsaParameter.h"
#include "WtVsgParameter.h"
#include "WtInfo.h"
#include "WtDemo.h"
#include "WtIqSwap.h"
#include "WtResult.h"

using namespace System;

namespace AILinkFactoryAuto{
	namespace Instrument {
		namespace WtApi {
			public ref class WlanTester
			{
			public:
				WtVsaParameter^ WtVsaInfo;
				WtVsgParameter^ WtVsgInfo;

			public:
				static void WtDllInitialize();

				static void WtDllTerminate();

				void WtConnect(String^ ipAddr);

				void WtForceConnect(String^ ipAddr);

				void WtDisConnect();

				WtInfo^ WtGetTesterVersion();

				void WtSetExternalGain(double extGain);

				void WtGetDefaultParameter();

				void WtSetVsa();

				void WtSetVsg();

				void WtDataCapture();

				void WtSetVsaAutoRange();

				void WtStopDataCapture();

				void WtGetResult(WtResult^ wtResult);

				void WtStartVsg();

				void WtStopVsg();

			private:
				String^ Char2String(char* data);
				char* String2Char(String^ data);
				
			private:
				int connID;
			};
		}
	}
}
