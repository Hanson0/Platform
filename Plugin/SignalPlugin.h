#pragma once

#ifndef __SIGNAL_PLUGIN_H__
#define __SIGNAL_PLUGIN_H__

#include "Signal.h"

class SignalPlugin : public Signal
{
public:
	SignalPlugin();

	virtual void SetPow(double dBm);			//设置功率
	virtual double GetPow() const;				//获取功率

	virtual void SetPow2(double dBm);			//设置功率，仅80+80使用
	virtual double GetPow2() const;				//获取功率，仅80+80使用

	virtual void SetAntenna(int ant);			//设置天线
	virtual int GetAntenna() const;				//获取天线

	virtual void SetAntenna2(int ant);			//设置天线，仅80+80使用
	virtual int GetAntenna2() const;			//获取天线，仅80+80使用

	virtual void SetChannel(int channel);		//设置信道
	virtual int GetChannel() const;				//获取信道

	virtual void SetChannel2(int channel);		//设置信道，仅80+80使用
	virtual int GetChannel2() const;			//获取信道，仅80+80使用

	virtual void SetFreqHz(double dHz);			//设置频点
	virtual double GetFreqHz() const;			//获取频点

	virtual void SetFreqHz2(double dHz);		//设置频点，仅80+80使用
	virtual double GetFreqHz2() const;			//获取频点，仅80+80使用

	virtual void SetFreqOffsetHz(double dHz);	//设置频点偏移
	virtual double GetFreqOffsetHz() const;		//获取频点偏移

	virtual void SetExtAtten(double dB);		//设置外部增益
	virtual double GetExtAtten() const;			//获取外部增益

	virtual void SetExtAtten2(double dB);		//设置外部增益，仅80+80使用
	virtual double GetExtAtten2() const;		//获取外部增益，仅80+80使用

	virtual void SetMcs(int mcs);				//设置MCS
	virtual int GetMcs() const;					//获取MCS

	virtual void SetFrameGap(double frameGap);		//设置帧间隔
	virtual double GetFrameGap() const;				//获取帧间隔

	virtual void SetFrameCnt(int frameCnt);			//设置帧数
	virtual int GetFrameCnt() const;				//获取帧数

	virtual void SetPreamble(int preamble);			//设置长短前导
	virtual int GetPreamble() const;				//获取长短前导

	virtual void SetFrameTime(double frameTime);	//设置一帧所用时间,us
	virtual double GetFrameTime() const;			//获取一帧采样时间

	virtual void SetDataLen(int dataLen);			//设置数据长度
	virtual int GetDataLen() const;					//获取数据长度

	virtual void SetGi(int gi);						//设置GI模式
	virtual int GetGi() const;						//获取GI模式

	virtual void SetPayload(int payload);			//设置Payload
	virtual int GetPayload() const;					//获取Payload

	virtual double EvluateFramTime() const;			//获取最小采样长度

	virtual double GetDataRate() const;				//获取速率
	virtual int GetFreqGroup() const;				//获取频偏组

	virtual int GetDemod() const;					//获取模式
	virtual int GetBw() const;						//获取带宽

	virtual void SetNss(int nss);					//设置NSS
	virtual int GetNss() const;						//获取NSS

	virtual bool IsMcsValid(int mcs) const;			//判断MCS是否合法
	virtual int ChangeDataRateToMcs(double dataRate) const;		//将速率转换成MCS
	virtual double ChangeMcsToDataRate(int mcs) const;			//将MCS转换成速率
	virtual bool IsStandardDataRate(double dataRate) const;		//判断速率是否标准
	virtual bool IsChannelValid(int channel) const;				//判断channel是否合法

	virtual bool IsStandardFreq(double freq) const;				//判断频率是否合法 WIFI 按5M间隔进行信道判断

	virtual void SetUsed2Port(bool isUsed);			//设置是否使用2个端口，仅80+80使用
	virtual bool GetUsed2Port() const;				//获取是否使用2个端口，仅80+80使用

public:
	double WtEvluateFramTime;
	double DataRate;
	int FreqGroup;
	int Demod;
	int Bw;

private:
	double pow;
	double pow2;
	int antenna;
	int antenna2;
	int channel;
	int channel2;
	double freqHz;
	double freqHz2;
	double freqOffsetHz;
	double extAtten;
	double extAtten2;
	int mcs;
	double frameGap;
	int frameCnt;
	int preamble;
	double frameTime;
	int dataLen;
	int gi;
	int payLoad;
	int nss;
	bool used2Port;
};

#endif