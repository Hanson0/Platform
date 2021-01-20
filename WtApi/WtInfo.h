#pragma once

using namespace System;

namespace AILinkFactoryAuto {
	namespace Instrument {
		namespace WtApi {
			public ref class WtInfo
			{
			public:
				String^ Ip;
				String^ SubMask;
				String^ GateAddr;
				String^ Sn;
				String^ Name;
				String^ MacAddr;
				String^ FwVersion;
				String^ HwVersion;
				String^ RfVersion;
				String^ CalDate;

			public:
				virtual String^ ToString() override;
			};		
		}
	}
}