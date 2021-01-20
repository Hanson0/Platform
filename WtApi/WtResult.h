#pragma once

#include "WtResParamString.h"

using namespace System;

namespace AILinkFactoryAuto {
	namespace Instrument {
		namespace WtApi {
			public ref class WtResult
			{
			public:
				String^ AnaParamString;
				double Result;
				String^ Description;
				String^ Unit;

			public:
				virtual String^ ToString() override;
			};
		}
	}
}