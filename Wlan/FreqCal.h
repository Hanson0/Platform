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
			namespace Executer
			{
				public ref class FreqCalExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};
			}
		}
	}
}