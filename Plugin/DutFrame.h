// Wlantester.h

#pragma once
#include "windows.h"
#include "IDut.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace AILinkFactoryAuto::Core;
using namespace AILinkFactoryAuto::Task::Property;

typedef int(*create_plugin)();
typedef void(*destroy_plugin)(HANDLE dut);
typedef void(*get_plugin_version)(char *version, int verSize);

namespace AILinkFactoryAuto {
	namespace Wlan {
		namespace Plugin {

			public enum class WtDut
			{
				WT_DUT_GENERICITY,					//默认通用类型
				WT_DUT_WIFI_2G,						//2.4G
				WT_DUT_WIFI_5G,						//5.8G
				WT_DUT_BT,							//蓝牙
				WT_DUT_ZIGBEE,						//Zigbee
				WT_DUT_CW,							//CW
				WT_DUT_LoRa,						//LORA
				WT_DUT_Lrwpan						//LRWPAN
			};

			public enum class WtTxMode
			{
				TX_MODE_FREQ_CAL,					//发送模式为频偏校准
				TX_MODE_POWER_CAL,					//发送模式为功率校准
				TX_MODE_TX_VERIFY,					//发送模式为TX测试
				TX_MODE_COMMON,						//通用发送模式
				TX_MODE_POWER_AND_FREQ_CAL,			//功率频偏同时校准
				TX_MODE_CAL_LOSS					//发送模式为金机校线测试
			};

			public enum class WtOperateType
			{
				eumElement_read,	//读取
				eumElement_write,	//写入
			};

			public enum class WtCfgType
			{
				CFG_BT_Limit,		//来源于WT_BT_LIMIT
				CFG_Dut_Mimo,		//来源于WT_DUT_MIMO
				CFG_Flow,			//来源于WT_FLOW
				CFG_Mac,			//来源于WT_MAC
				CFG_Tester,			//来源于WT_TESTER
				CFG_Wifi_Limit,		//来源于WT_WIFI_LIMIT
				CFG_Zigbee_Limit,	//来源于WT_ZIGBEE_LIMIT
				CFG_Atten_Dut,		//来源于WT_ATTEN_DUT_X
				CFG_Platform_Info	//来源于平台
			};

			public enum class WtDemodPlugin {
				eumDemod_11ag,
				eumDemod_11b,
				eumDemod_11n_20M,
				eumDemod_11n_40M,

				eumDemod_11ac_20M,
				eumDemod_11ac_40M,
				eumDemod_11ac_80M,
				eumDemod_11ac_160M,
				eumDemod_11ac_80M_80M,
				eumDemod_BT = 9,
				eumDemod_Zigbee,
				eumDemod_11ah_1M,
				eumDemod_11ah_2M,
				eumDemod_11ah_4M,
				eumDemod_11ah_8M,
				eumDemod_11ah_16M,
				eumDemod_CW,
				eumDemod_11p_5M,
				eumDemod_11p_10M,
				eumDemod_LoRa_125K,
				eumDemod_LoRa_250K,
				eumDemod_LoRa_500K,
				eumDemod_11ax_20M,
				eumDemod_11ax_40M,
				eumDemod_11ax_80M,
				eumDemod_11ax_160M,
				eumDemod_11ax_80_80M,
				eumDemod_Lrwpan_FSK,
				eumDemod_Lrwpan_OQPSK,
				eumDemod_Lrwpan_OFDM,
			};

			public enum class WtBw {
				eumBw_20M,
				eumBw_40M,
				eumBw_80M,
				eumBw_160M
			};

			public enum class WtGi {
				eumGiLong,
				eumGiShort
			};

			public enum class WtChain
			{
				CHAIN0,
				CHAIN1,
				CHAIN2,
				CHAIN3,
				CHAIN4,
				CHAIN5,
				CHAIN6,
				CHAIN7,
			};

			public enum class InfoType
			{
				STUDIO,
				WLAN_TESER
			};

			public enum class WtMacType
			{
				eumMacIdx_Wifi = 0,					//WIFI 2.4G
				eumMacIdx_Lan = 1,					//LAN
				eumMacIdx_Wan = 2,					//WAN
				eumMacIdx_Wifi_5G = 3,				//WIFI 5.8G
				eumMacIdx_Bt = 4,						//蓝牙
				eumMacIdx_Wan0_1 = 5,					//WAN
				eumMacIdx_Wan0_2 = 6,					//WAN
				eumMacIdx_Wan0_3 = 7,					//WAN
				eumMacIdx_Wan0_4 = 8,					//WAN
				eumMacIdx_Wan1_1 = 9,					//WAN
				eumMacIdx_Wan1_2 = 10,				//WAN
				eumMacIdx_Wan1_3 = 11,				//WAN
				eumMacIdx_Wan1_4 = 12,				//WAN
				eumMacIdx_Ex0 = 13,					//预留枚举
				eumMacIdx_Ex1 = 14,					//预留枚举
				eumMacIdx_MaxCount,					//mac总数
			};

			public ref class SignalData
			{
			public:
				int GetBand();

			public:
				int Pow;
				double Freq;
				WtDemodPlugin WtDemodPlugin;
				int Antenna;
				WtBw WtBw;
				int Mcs;
				int Preamble;
				WtGi WtGi;
			};

			public ref class RxResult
			{
			public:
				double Ber;
				int BitCnt;
				int FrameCnt;
				int Rssi;
			};

			public ref class DutFrame
			{
			public:
				static ILog^ Log;
				static InfoType InfoType;

				String^ Char2String(char* data);
				char* String2Char(String^ data);

				DutFrame(String^ filename);
				void SetCallBack();
				String^ GetPluginVersion();
				void DestroyPlugin();
				void SetDutId(int id);
				void Init();
				bool IsDutReady();
				void Open(WtDut wtDut);
				void Close(WtDut wtDut);

				void CalBegin(WtDut wtDut);
				void CalEnd(WtDut wtDut);

				void SaveCalData(WtDut wtDut);

				void SetSignal(SignalData^ signalData);

				int GetAntCount(int band);
				void TxFrame(WtTxMode txMode);
				void TxStop();

				void GetTgtPwrAndPwrReg(SignalData^ signalData);
				void GetTargetPowerAndReg(SignalData^ signalData, StringBuilder^ targetPow, StringBuilder^ regVal);
				void AdjustFreqReg(double freqErrPpm);
				void AdjustPowerReg(double powerErr);

				bool SetFreqCalRegVal(int band, int regVal);
				bool SetPwrCalRegVal(int band, int ant, int channel, int regVal);

				void RxStart();
				void GetRxResult(RxResult^ rxResult);
				void RxStop();

				void TempratureCompensation();
				void SetMac(WtMacType wtMacType, String^ mac);
				void GetMac(WtMacType wtMacType, StringBuilder^ mac);
				void SaveCalData();
				void WriteEfuse(WtDut wtDut);
				void CheckEfuse(WtDut wtDut);

			private:
				HMODULE hmodule;
				HANDLE handleDut;
				create_plugin createPlugin;
				destroy_plugin destroyPlugin;
				get_plugin_version getPluginVersion;
				
			public:
				static Dictionary<String^, Dictionary<String^, KeyValue^>^>^ WtSetUpDic;
				int FreqRegVal;
				int PowerRegVal;
			};
		}
	}
}
