// Wlan.h

#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections::Generic;
using namespace System::Drawing::Design;
using namespace AILinkFactoryAuto::Task;
using namespace AILinkFactoryAuto::Task::Executer;
using namespace AILinkFactoryAuto::Task::Property;
using namespace AILinkFactoryAuto::Task::Property::Converter;
using namespace AILinkFactoryAuto::Wlan::Plugin;

namespace AILinkFactoryAuto {
	namespace Task
	{
		namespace Wlan
		{
			namespace Executer
			{
				public ref class LoadDllExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				//public ref class WtSetUpExecuter : IExecuter
				//{
				//public:
				//	virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				//};

				public ref class IsDutReadyExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class DutInitExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class OpenDutExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class CloseDutExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class ConnectInstrumentExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class DisconnectInstrumentExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class CalBeginExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class CalEndExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class TempratureCompenstationExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class SetMacAddressExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class SaveCalDataExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class WriteEfuseExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};

				public ref class CheckEfuseExecuter : IExecuter
				{
				public:
					virtual void Run(IProperties^ properties, GlobalDic<String^, Object^>^ globalDic);
				};
			}

			namespace Property
			{
				public ref class LoadDllProperties : CommonProperties
				{
				public:
					[Category("Common"), Description("iTester's dll")]
					property String^ Filename;

					[Category("Common"), Description("DUT sequence")]
					property int Sequence;

					[Category("Common"), Description("WT_SETUP"), EditorAttribute(DictionaryUiTypeEditor::typeid, UITypeEditor::typeid)]
					property Dictionary<String^, KeyValue^>^ WtSetUp;

					[Category("Common"), Description("info type")]
					property InfoType InfoType;
				};

				//public ref class WtSetUpProperties : CommonProperties
				//{
				//public:
				//	[Category("Common"), Description("WT_SETUP"), EditorAttribute(DictionaryUiTypeEditor::typeid, UITypeEditor::typeid)]
				//	property Dictionary<String^, KeyValue^>^ WtSetUp;
				//};

				public ref class IsDutReadyProperties : CommonProperties
				{
				};

				public ref class DutInitProperties : CommonProperties
				{
				};

				public ref class OpenDutProperties : CommonProperties
				{
				public:
					[Category("Common"), Description("dut type")]
					property WtDut WtDut;
				};

				public ref class CloseDutProperties : CommonProperties
				{
				public:
					CloseDutProperties();

				public:
					[Category("Common"), Description("dut type")]
					property WtDut WtDut;
				};

				public ref class ConnectInstrumentProperties : CommonProperties
				{
				public:
					[Category("Common"), Description("ip address")]
					property String^ ip;
				};

				public ref class CalBeginProperties : CommonProperties
				{
				public:
					[Category("Common"), Description("dut type")]
					property WtDut WtDut;
				};

				public ref class CalEndProperties : CommonProperties
				{
				public:
					[Category("Common"), Description("dut type")]
					property WtDut WtDut;
				};

				public ref class DisconnectInstrumentProperties : CommonProperties
				{
				};

				public ref class WriteEfuseProperties : CommonProperties
				{
				public:
					[Category("Common"), Description("dut type")]
					property WtDut WtDut;
				};

				public ref class CheckEfuseProperties : CommonProperties
				{
				public:
					[Category("Common"), Description("dut type")]
					property WtDut WtDut;
				};
			}

			namespace Utils
			{
				public enum class WtMcs
				{
					MCS_1M,
					MCS_2M,
					MCS_5_5M,
					MCS_11M,
					MCS_6M,
					MCS_9M,
					MCS_12M,
					MCS_18M,
					MCS_24M,
					MCS_36M,
					MCS_48M,
					MCS_54M,
					MCS0,
					MCS1,
					MCS2,
					MCS3,
					MCS4,
					MCS5,
					MCS6,
					MCS7,
					MCS8,
					MCS9,
					MCS10,
					MCS11,
				};

				public ref class WtUtils
				{
				public:
					static int WtMcs2Int(WtMcs wtMcs);
				};
			}
		}
	}
}
