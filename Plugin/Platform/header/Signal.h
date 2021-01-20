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
	eumAntMax = 8,			//11n标准中最多使用4天线,一般无线产品不会超过3天线
	eumChannelMax = 200,	//2.4G使用channel[1-14],5G使用[36-64],[100-140],[149-165]
	eumChannelGroupMax = eumChannelMax,
	eumMcsMax = 76,			//11n最多有76个MCS

	eum11gMcsMax=8,
	eum11bMcsMax=4,
	eum11nMcsMax=16,		//单天线是8，双天线16
	eum11acMcsMax=20	//单天线是10，双天线20
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

//Zigbee 速率枚举
enum
{
	enumZigbee = 1,
};

class Signal
{
public:
	virtual void SetPow(double dBm) = 0;			//设置功率
	virtual double GetPow() const = 0;				//获取功率

	virtual void SetPow2(double dBm) = 0;			//设置功率，仅80+80使用
	virtual double GetPow2() const = 0;				//获取功率，仅80+80使用

	virtual void SetAntenna(int ant) = 0;			//设置天线
	virtual int GetAntenna() const = 0;				//获取天线

	virtual void SetAntenna2(int ant) = 0;			//设置天线，仅80+80使用
	virtual int GetAntenna2() const = 0;			//获取天线，仅80+80使用

	virtual void SetChannel(int channel) = 0;		//设置信道
	virtual int GetChannel() const = 0;				//获取信道

	virtual void SetChannel2(int channel) = 0;		//设置信道，仅80+80使用
	virtual int GetChannel2() const = 0;			//获取信道，仅80+80使用

	virtual void SetFreqHz(double dHz) = 0;			//设置频点
	virtual double GetFreqHz() const = 0;			//获取频点

	virtual void SetFreqHz2(double dHz) = 0;		//设置频点，仅80+80使用
	virtual double GetFreqHz2() const = 0;			//获取频点，仅80+80使用

	virtual void SetFreqOffsetHz(double dHz) = 0;	//设置频点偏移
	virtual double GetFreqOffsetHz() const = 0;		//获取频点偏移

	virtual void SetExtAtten(double dB) = 0;		//设置外部增益
	virtual double GetExtAtten() const = 0;			//获取外部增益

	virtual void SetExtAtten2(double dB) = 0;		//设置外部增益，仅80+80使用
	virtual double GetExtAtten2() const = 0;		//获取外部增益，仅80+80使用

	virtual void SetMcs(int mcs) = 0;				//设置MCS
	virtual int GetMcs() const = 0;					//获取MCS

	virtual void SetFrameGap(double frameGap) = 0;		//设置帧间隔
	virtual double GetFrameGap() const = 0;				//获取帧间隔

	virtual void SetFrameCnt(int frameCnt) = 0;			//设置帧数
	virtual int GetFrameCnt() const = 0;				//获取帧数

	virtual void SetPreamble(int preamble) = 0;			//设置长短前导
	virtual int GetPreamble() const = 0;				//获取长短前导

	virtual void SetFrameTime(double frameTime) = 0;	//设置一帧所用时间,us
	virtual double GetFrameTime() const = 0;			//获取一帧采样时间

	virtual void SetDataLen(int dataLen) = 0;			//设置数据长度
	virtual int GetDataLen() const = 0;					//获取数据长度

	virtual void SetGi(int gi) = 0;						//设置GI模式
	virtual int GetGi() const = 0;						//获取GI模式

	virtual void SetPayload(int payload) = 0;			//设置Payload
	virtual int GetPayload() const = 0;					//获取Payload

	virtual double EvluateFramTime() const = 0;			//获取最小采样长度

	virtual double GetDataRate() const = 0;				//获取速率
	virtual int GetFreqGroup() const = 0;				//获取频偏组

	virtual int GetDemod() const = 0;					//获取模式
	virtual int GetBw() const = 0;						//获取带宽

	virtual void SetNss(int nss) = 0;					//设置NSS
	virtual int GetNss() const = 0;						//获取NSS

	virtual bool IsMcsValid(int mcs) const = 0;			//判断MCS是否合法
	virtual int ChangeDataRateToMcs(double dataRate) const = 0;		//将速率转换成MCS
	virtual double ChangeMcsToDataRate(int mcs) const = 0;			//将MCS转换成速率
	virtual bool IsStandardDataRate(double dataRate) const = 0;		//判断速率是否标准
	virtual bool IsChannelValid(int channel) const = 0;				//判断channel是否合法

	virtual bool IsStandardFreq(double freq) const = 0;				//判断频率是否合法 WIFI 按5M间隔进行信道判断

	virtual void SetUsed2Port(bool isUsed) = 0;			//设置是否使用2个端口，仅80+80使用
	virtual bool GetUsed2Port() const = 0;				//获取是否使用2个端口，仅80+80使用
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

