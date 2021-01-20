#pragma once

using namespace System;
using namespace AILinkFactoryAuto::Task::Executer;
using namespace AILinkFactoryAuto::Task::Property;

namespace AILinkFactoryAuto {
	namespace Task
	{
		namespace Wlan
		{
			namespace Executer
			{
				public ref class PowerCalExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};
			}
		}
	}
}