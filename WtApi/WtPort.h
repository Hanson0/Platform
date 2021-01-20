#pragma once

using namespace System;

namespace AILinkFactoryAuto {
	namespace Instrument {
		namespace WtApi {
			public enum class WtPort
			{
				// Port has been disabled.
				WT_PORT_OFF = 1,
				// RF port 1
				WT_PORT_RF1 = 2,
				// RF port 2
				WT_PORT_RF2 = 3,
				// RF port 3, WT208 only
				WT_PORT_RF3 = 4,
				// RF port 4, WT208 only
				WT_PORT_RF4 = 5,

				// RF port 5, WT208C only
				WT_PORT_RF5 = 6,
				// RF port 6, WT208C only
				WT_PORT_RF6 = 7,
				// RF port 7, WT208C only
				WT_PORT_RF7 = 8,
				// RF port 8, WT208C only
				WT_PORT_RF8 = 9,

				WT_PORT_MAX
			};
		}
	}
}