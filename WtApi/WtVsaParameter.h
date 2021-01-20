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
				double  Freq;				//VSA�ز�Ƶ��,��λ��Hz
				double  MaxPower;			//����������,dBm; (�����ʵ������������Ĺ��ʻ������ټ�12dB��������չ��ʷ�Χδ֪����������Auto Range)
				double  SmpTime;			//����ʱ��,us
				WtPort     RfPort;             //ָ��VSAʹ�õ�RF�˿�
				WtTrigType     TrigType;			//����ģʽ,WT_TRIG_TYPE_ENUM
				double  TrigLevel;			//������ƽ,��max_power�Ĳ��,dB
				double  TrigTimeout;		//�����ȴ���ʱ,sec����ʱ����TimeoutWaiting��ʱ���໥������
				double  TrigPretime;		//��������ʱ��,��������ǰ����ʱ���ڵ�����,us

				WtDemo  Demod;              //802.11 ����ģʽ.WT_DEMOD_ENUM
				WtIqSwap IqSwap;				//IQ����(Ƶ�׷�ת). WT_IQ_SWAP_ENUM

				int     PhCorr;				//802.11 a/g/n/ac ��λ����. WT_PH_CORR_ENUM
				int     ChEstimate;			//802.11 a/g/n/ac ͨ������. WT_CH_EST_ENUM
				int     SymTimCorr;			//802.11 a/g/n/ac ʱ�����. WT_SYM_TIM_ENUM
				int     FreqSync;			//802.11 a/g/n/ac Ƶ��ͬ��. WT_FREQ_SYNC_ENUM
				int     AmplTrack;			//802.11 a/g/n/ac ���ȸ���. WT_AMPL_TRACK_ENUM

				int     EvmMethod11b;		//802.11 b EVM��ʽ.  WT_11B_METHOD_ENUM
				int     DcRemoval;			//802.11 b ֱ��ȥ��. WT_DC_REMOVAL_ENUM
				int     EqTaps;				//802.11 b ��������. WT_EQ_ENUM
				int     CckPhCorr;			//802.11 b ��λ����. WT_PH_CORR_11b_ENUM

				int     BtRate;				//Bluetooth����, WT_BT_DATARATE
				int     BtPacketType;		//Bluetooth������, WT_BT_PACKETTYPE(Ĭ������ΪWT_BT_PACKETTYPE_NULL����)

				int     TimeoutWaiting;     //�ڶ���������£��ȴ������ʱ�䣬Ĭ��ֵΪ8�룬��λsec

			public:
				virtual String^ ToString() override;
			};
		}
	}
}