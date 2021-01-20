#pragma once

#ifndef __SIGNAL_H__
#define __SIGNAL_H__

enum{
	eumDemod_11ag,
	eumDemod_11b,
	eumDemod_11n_20M,
	eumDemod_11n_40M,

	eumDemodMax_11n,
	eumDemod_11ac_20M = eumDemodMax_11n,
	eumDemod_11ac_40M,
	eumDemod_11ac_80M,
	eumDemodMax_11ac_80M,
	eumDemod_11ac_160M = eumDemodMax_11ac_80M,
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
	eumDemodMax,
};
enum{
	eumBw_20M,
	eumBw_40M,
	eumBw_80M,
	eumBw_160M,
	eumBwMax
};
enum{
	eumGiLong,
	eumGiShort,
	eumGiMax
};
enum{
	eumFreqGroup2_4G,
	eumFreqGroup5G,
	eumFreqGroupBT,
	eumFreqGroupZigbee,
	eumFreqGroupLoRa,
	eumFreqGroupInvalid,
};
enum{
	eum5GSubChannelGroup_L,		//[36-64]
	eum5GSubChannelGroup_M,		//[100-140]
	eum5GSubChannelGroup_H,		//[149-165]

	eum5GSubChannelGroupMax		//[149-165]
};
enum{
	eumFreqGroupMax = 2,	//2.4G 5G
	eumAntMax = 8,			//11n��׼�����ʹ��4����,һ�����߲�Ʒ���ᳬ��3����
	eumChannelMax = 200,	//2.4Gʹ��channel[1-14],5Gʹ��[36-64],[100-140],[149-165]
	eumChannelGroupMax = eumChannelMax,
	eumMcsMax = 76,			//11n�����76��MCS

	eum11gMcsMax=8,
	eum11bMcsMax=4,
	eum11nMcsMax=16,		//��������8��˫����16
	eum11acMcsMax=20	//��������10��˫����20
};


enum {
	enumBT_DH1 = 1,
	enumBT_DH3,
	enumBT_DH5,
	enumBT_2DH1,
	enumBT_2DH3,
	enumBT_2DH5,
	enumBT_3DH1,
	enumBT_3DH3,
	enumBT_3DH5,
	enumBT_LE,
	enumBT_LE1M = enumBT_LE,
	enumBT_LE2M,
	enumBT_LE_125K,
	enumBT_LE_500K,
};

enum
{
	enumBT_0F,		// test f1
	enumBT_55,		// test f2
	enumBT_PRBS9,
	enumBT_FF
};

//Zigbee ����ö��
enum
{
	enumZigbee = 1,
};

class Signal
{
public:
	virtual void SetPow(double dBm) = 0;			//���ù���
	virtual double GetPow() const = 0;				//��ȡ����

	virtual void SetPow2(double dBm) = 0;			//���ù��ʣ���80+80ʹ��
	virtual double GetPow2() const = 0;				//��ȡ���ʣ���80+80ʹ��

	virtual void SetAntenna(int ant) = 0;			//��������
	virtual int GetAntenna() const = 0;				//��ȡ����

	virtual void SetAntenna2(int ant) = 0;			//�������ߣ���80+80ʹ��
	virtual int GetAntenna2() const = 0;			//��ȡ���ߣ���80+80ʹ��

	virtual void SetChannel(int channel) = 0;		//�����ŵ�
	virtual int GetChannel() const = 0;				//��ȡ�ŵ�

	virtual void SetChannel2(int channel) = 0;		//�����ŵ�����80+80ʹ��
	virtual int GetChannel2() const = 0;			//��ȡ�ŵ�����80+80ʹ��

	virtual void SetFreqHz(double dHz) = 0;			//����Ƶ��
	virtual double GetFreqHz() const = 0;			//��ȡƵ��

	virtual void SetFreqHz2(double dHz) = 0;		//����Ƶ�㣬��80+80ʹ��
	virtual double GetFreqHz2() const = 0;			//��ȡƵ�㣬��80+80ʹ��

	virtual void SetFreqOffsetHz(double dHz) = 0;	//����Ƶ��ƫ��
	virtual double GetFreqOffsetHz() const = 0;		//��ȡƵ��ƫ��

	virtual void SetExtAtten(double dB) = 0;		//�����ⲿ����
	virtual double GetExtAtten() const = 0;			//��ȡ�ⲿ����

	virtual void SetExtAtten2(double dB) = 0;		//�����ⲿ���棬��80+80ʹ��
	virtual double GetExtAtten2() const = 0;		//��ȡ�ⲿ���棬��80+80ʹ��

	virtual void SetMcs(int mcs) = 0;				//����MCS
	virtual int GetMcs() const = 0;					//��ȡMCS

	virtual void SetFrameGap(double frameGap) = 0;		//����֡���
	virtual double GetFrameGap() const = 0;				//��ȡ֡���

	virtual void SetFrameCnt(int frameCnt) = 0;			//����֡��
	virtual int GetFrameCnt() const = 0;				//��ȡ֡��

	virtual void SetPreamble(int preamble) = 0;			//���ó���ǰ��
	virtual int GetPreamble() const = 0;				//��ȡ����ǰ��

	virtual void SetFrameTime(double frameTime) = 0;	//����һ֡����ʱ��,us
	virtual double GetFrameTime() const = 0;			//��ȡһ֡����ʱ��

	virtual void SetDataLen(int dataLen) = 0;			//�������ݳ���
	virtual int GetDataLen() const = 0;					//��ȡ���ݳ���

	virtual void SetGi(int gi) = 0;						//����GIģʽ
	virtual int GetGi() const = 0;						//��ȡGIģʽ

	virtual void SetPayload(int payload) = 0;			//����Payload
	virtual int GetPayload() const = 0;					//��ȡPayload

	virtual double EvluateFramTime() const = 0;			//��ȡ��С��������

	virtual double GetDataRate() const = 0;				//��ȡ����
	virtual int GetFreqGroup() const = 0;				//��ȡƵƫ��

	virtual int GetDemod() const = 0;					//��ȡģʽ
	virtual int GetBw() const = 0;						//��ȡ����

	virtual void SetNss(int nss) = 0;					//����NSS
	virtual int GetNss() const = 0;						//��ȡNSS

	virtual bool IsMcsValid(int mcs) const = 0;			//�ж�MCS�Ƿ�Ϸ�
	virtual int ChangeDataRateToMcs(double dataRate) const = 0;		//������ת����MCS
	virtual double ChangeMcsToDataRate(int mcs) const = 0;			//��MCSת��������
	virtual bool IsStandardDataRate(double dataRate) const = 0;		//�ж������Ƿ��׼
	virtual bool IsChannelValid(int channel) const = 0;				//�ж�channel�Ƿ�Ϸ�

	virtual bool IsStandardFreq(double freq) const = 0;				//�ж�Ƶ���Ƿ�Ϸ� WIFI ��5M��������ŵ��ж�

	virtual void SetUsed2Port(bool isUsed) = 0;			//�����Ƿ�ʹ��2���˿ڣ���80+80ʹ��
	virtual bool GetUsed2Port() const = 0;				//��ȡ�Ƿ�ʹ��2���˿ڣ���80+80ʹ��
};


//#ifdef COMMON_EXPORTS
//#define SIGNAL_Decl __declspec(dllexport)
//#else
//#define SIGNAL_Decl __declspec(dllimport)
//#endif

#define SIGNAL_Decl

extern "C" SIGNAL_Decl Signal *CreateSignal(int demode);
extern "C" SIGNAL_Decl void DeleteSignal(Signal *signal);

extern "C" SIGNAL_Decl int ChangeDataRateToMcs(int demode, double dataRate);
extern "C" SIGNAL_Decl double ChangeMcsToDataRate(int demode, int mcs);

extern "C" SIGNAL_Decl double ChangeChannelToFreqHz(int demode, int mcs, int channel);
extern "C" SIGNAL_Decl int ChangeFreqHzToChannel(int demode, int mcs, double FreqHz);


#endif

