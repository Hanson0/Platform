#pragma once

#include "WtDemo.h"
#include "WtIqSwap.h"
#include "WtPort.h"
#include "WtTrigType.h"

using namespace System;

namespace AILinkFactoryAuto {
	namespace Instrument {
		namespace WtApi {
			public ref class WtVsaParameter
			{
			public:
				double  Freq;				//VSA载波频率,单位：Hz
				double  MaxPower;			//输入的最大功率,dBm; (最好在实际输出到仪器的功率基础上再加12dB，如果接收功率范围未知，建议事先Auto Range)
				double  SmpTime;			//采样时间,us
				WtPort     RfPort;             //指定VSA使用的RF端口
				WtTrigType     TrigType;			//触发模式,WT_TRIG_TYPE_ENUM
				double  TrigLevel;			//触发电平,与max_power的差距,dB
				double  TrigTimeout;		//触发等待超时,sec（该时间与TimeoutWaiting的时间相互独立）
				double  TrigPretime;		//触发保留时间,保留触发前若干时间内的数据,us

				WtDemo  Demod;              //802.11 分析模式.WT_DEMOD_ENUM
				WtIqSwap IqSwap;				//IQ交换(频谱反转). WT_IQ_SWAP_ENUM

				int     PhCorr;				//802.11 a/g/n/ac 相位跟踪. WT_PH_CORR_ENUM
				int     ChEstimate;			//802.11 a/g/n/ac 通道估计. WT_CH_EST_ENUM
				int     SymTimCorr;			//802.11 a/g/n/ac 时序跟踪. WT_SYM_TIM_ENUM
				int     FreqSync;			//802.11 a/g/n/ac 频率同步. WT_FREQ_SYNC_ENUM
				int     AmplTrack;			//802.11 a/g/n/ac 幅度跟踪. WT_AMPL_TRACK_ENUM

				int     EvmMethod11b;		//802.11 b EVM方式.  WT_11B_METHOD_ENUM
				int     DcRemoval;			//802.11 b 直流去除. WT_DC_REMOVAL_ENUM
				int     EqTaps;				//802.11 b 均衡类型. WT_EQ_ENUM
				int     CckPhCorr;			//802.11 b 相位跟踪. WT_PH_CORR_11b_ENUM

				int     BtRate;				//Bluetooth速率, WT_BT_DATARATE
				int     BtPacketType;		//Bluetooth包类型, WT_BT_PACKETTYPE(默认设置为WT_BT_PACKETTYPE_NULL即可)

				int     TimeoutWaiting;     //在多连接情况下，等待的最大时间，默认值为8秒，单位sec

			public:
				virtual String^ ToString() override;
			};
		}
	}
}