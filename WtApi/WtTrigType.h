#pragma once

using namespace System;

namespace AILinkFactoryAuto {
	namespace Instrument {
		namespace WtApi {
			public enum class WtTrigType
			{
				// Free running ADC sampling.
				WT_TRIG_TYPE_FREE_RUN,
				// ADC External Trigger selected.
				WT_TRIG_TYPE_EXT,
				// ADC IF Trigger selected - trigger calibration will be performed.
				WT_TRIG_TYPE_IF,
				WT_TRIG_TYPE_IF_NO_CAL
			};
		}
	}
}