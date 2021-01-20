#pragma once

#ifndef __SIGNAL_PLUGIN_H__
#define __SIGNAL_PLUGIN_H__

#include "Signal.h"

class SignalPlugin : public Signal
{
public:
	SignalPlugin();

	virtual void SetPow(double dBm);			//���ù���
	virtual double GetPow() const;				//��ȡ����

	virtual void SetPow2(double dBm);			//���ù��ʣ���80+80ʹ��
	virtual double GetPow2() const;				//��ȡ���ʣ���80+80ʹ��

	virtual void SetAntenna(int ant);			//��������
	virtual int GetAntenna() const;				//��ȡ����

	virtual void SetAntenna2(int ant);			//�������ߣ���80+80ʹ��
	virtual int GetAntenna2() const;			//��ȡ���ߣ���80+80ʹ��

	virtual void SetChannel(int channel);		//�����ŵ�
	virtual int GetChannel() const;				//��ȡ�ŵ�

	virtual void SetChannel2(int channel);		//�����ŵ�����80+80ʹ��
	virtual int GetChannel2() const;			//��ȡ�ŵ�����80+80ʹ��

	virtual void SetFreqHz(double dHz);			//����Ƶ��
	virtual double GetFreqHz() const;			//��ȡƵ��

	virtual void SetFreqHz2(double dHz);		//����Ƶ�㣬��80+80ʹ��
	virtual double GetFreqHz2() const;			//��ȡƵ�㣬��80+80ʹ��

	virtual void SetFreqOffsetHz(double dHz);	//����Ƶ��ƫ��
	virtual double GetFreqOffsetHz() const;		//��ȡƵ��ƫ��

	virtual void SetExtAtten(double dB);		//�����ⲿ����
	virtual double GetExtAtten() const;			//��ȡ�ⲿ����

	virtual void SetExtAtten2(double dB);		//�����ⲿ���棬��80+80ʹ��
	virtual double GetExtAtten2() const;		//��ȡ�ⲿ���棬��80+80ʹ��

	virtual void SetMcs(int mcs);				//����MCS
	virtual int GetMcs() const;					//��ȡMCS

	virtual void SetFrameGap(double frameGap);		//����֡���
	virtual double GetFrameGap() const;				//��ȡ֡���

	virtual void SetFrameCnt(int frameCnt);			//����֡��
	virtual int GetFrameCnt() const;				//��ȡ֡��

	virtual void SetPreamble(int preamble);			//���ó���ǰ��
	virtual int GetPreamble() const;				//��ȡ����ǰ��

	virtual void SetFrameTime(double frameTime);	//����һ֡����ʱ��,us
	virtual double GetFrameTime() const;			//��ȡһ֡����ʱ��

	virtual void SetDataLen(int dataLen);			//�������ݳ���
	virtual int GetDataLen() const;					//��ȡ���ݳ���

	virtual void SetGi(int gi);						//����GIģʽ
	virtual int GetGi() const;						//��ȡGIģʽ

	virtual void SetPayload(int payload);			//����Payload
	virtual int GetPayload() const;					//��ȡPayload

	virtual double EvluateFramTime() const;			//��ȡ��С��������

	virtual double GetDataRate() const;				//��ȡ����
	virtual int GetFreqGroup() const;				//��ȡƵƫ��

	virtual int GetDemod() const;					//��ȡģʽ
	virtual int GetBw() const;						//��ȡ����

	virtual void SetNss(int nss);					//����NSS
	virtual int GetNss() const;						//��ȡNSS

	virtual bool IsMcsValid(int mcs) const;			//�ж�MCS�Ƿ�Ϸ�
	virtual int ChangeDataRateToMcs(double dataRate) const;		//������ת����MCS
	virtual double ChangeMcsToDataRate(int mcs) const;			//��MCSת��������
	virtual bool IsStandardDataRate(double dataRate) const;		//�ж������Ƿ��׼
	virtual bool IsChannelValid(int channel) const;				//�ж�channel�Ƿ�Ϸ�

	virtual bool IsStandardFreq(double freq) const;				//�ж�Ƶ���Ƿ�Ϸ� WIFI ��5M��������ŵ��ж�

	virtual void SetUsed2Port(bool isUsed);			//�����Ƿ�ʹ��2���˿ڣ���80+80ʹ��
	virtual bool GetUsed2Port() const;				//��ȡ�Ƿ�ʹ��2���˿ڣ���80+80ʹ��

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