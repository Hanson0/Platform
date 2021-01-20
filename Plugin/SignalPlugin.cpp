#include "stdafx.h"
#include "SignalPlugin.h"

SignalPlugin::SignalPlugin()
{
	
}

void SignalPlugin::SetPow(double dBm)
{
	this->pow = dBm;
}

double SignalPlugin::GetPow() const
{
	return this->pow;
}

void SignalPlugin::SetPow2(double dBm)
{
	this->pow2 = dBm;
}

double SignalPlugin::GetPow2() const
{
	return this->pow2;
}

void SignalPlugin::SetAntenna(int ant)
{
	this->antenna = ant;
}

int SignalPlugin::GetAntenna() const
{
	return this->antenna;
}

void SignalPlugin::SetAntenna2(int ant)
{
	this->antenna2 = ant;
}

int SignalPlugin::GetAntenna2() const
{
	return this->antenna2;
}

void SignalPlugin::SetChannel(int channel)
{
	this->channel = channel;
}

int SignalPlugin::GetChannel() const
{
	return this->channel;
}

void SignalPlugin::SetChannel2(int channel)
{
	this->channel2 = channel;
}

int SignalPlugin::GetChannel2() const
{
	return this->channel2;
}

void SignalPlugin::SetFreqHz(double dHz)
{
	this->freqHz = dHz;
}

double SignalPlugin::GetFreqHz() const
{
	return this->freqHz;
}

void SignalPlugin::SetFreqHz2(double dHz)
{
	this->freqHz2 = dHz;
}

double SignalPlugin::GetFreqHz2() const
{
	return this->freqHz2;
}

void SignalPlugin::SetFreqOffsetHz(double dHz)
{
	this->freqOffsetHz = dHz;
}

double SignalPlugin::GetFreqOffsetHz() const
{
	return this->freqOffsetHz;
}

void SignalPlugin::SetExtAtten(double dB)
{
	this->extAtten = dB;
}

double SignalPlugin::GetExtAtten() const
{
	return this->extAtten;
}

void SignalPlugin::SetExtAtten2(double dB)
{
	this->extAtten2 = dB;
}

double SignalPlugin::GetExtAtten2() const
{
	return this->extAtten2;
}

void SignalPlugin::SetMcs(int mcs)
{
	this->mcs = mcs;
}

int SignalPlugin::GetMcs() const
{
	return this->mcs;
}

void SignalPlugin::SetFrameGap(double frameGap)
{
	this->frameGap = frameGap;
}

double SignalPlugin::GetFrameGap() const
{
	return this->frameGap;
}

void SignalPlugin::SetFrameCnt(int frameCnt)
{
	this->frameCnt = frameCnt;
}

int SignalPlugin::GetFrameCnt() const
{
	return this->frameCnt;
}

void SignalPlugin::SetPreamble(int preamble)
{
	this->preamble = preamble;
}

int SignalPlugin::GetPreamble() const
{
	return this->preamble;
}

void SignalPlugin::SetFrameTime(double frameTime)
{
	this->frameTime = frameTime;
}

double SignalPlugin::GetFrameTime() const
{
	return this->frameTime;
}

void SignalPlugin::SetDataLen(int dataLen)
{
	this->dataLen = dataLen;
}

int SignalPlugin::GetDataLen() const
{
	return this->dataLen;
}

void SignalPlugin::SetGi(int gi)
{
	this->gi = gi;
}

int SignalPlugin::GetGi() const
{
	return this->gi;
}

void SignalPlugin::SetPayload(int payload)
{
	this->payLoad = payLoad;
}

int SignalPlugin::GetPayload() const
{
	return this->payLoad;
}

double SignalPlugin::EvluateFramTime() const
{
	return this->WtEvluateFramTime;
}

double SignalPlugin::GetDataRate() const
{
	return this->DataRate;
}

int SignalPlugin::GetFreqGroup() const
{
	return this->FreqGroup;
}

int SignalPlugin::GetDemod() const
{
	return Demod;
}

int SignalPlugin::GetBw() const
{
	return Bw;
}

void SignalPlugin::SetNss(int nss)
{
	this->nss = nss;
}

int SignalPlugin::GetNss() const
{
	return this->nss;
}

bool SignalPlugin::IsMcsValid(int mcs) const
{
	return true;
}

int SignalPlugin::ChangeDataRateToMcs(double dataRate) const
{
	return 0;
}

double SignalPlugin::ChangeMcsToDataRate(int mcs) const
{
	return 0;
}

bool SignalPlugin::IsStandardDataRate(double dataRate) const
{
	return true;
}

bool SignalPlugin::IsChannelValid(int channel) const
{
	return true;
}

bool SignalPlugin::IsStandardFreq(double freq) const
{
	return true;
}

void SignalPlugin::SetUsed2Port(bool isUsed)
{
	this->used2Port = isUsed;
}

bool SignalPlugin::GetUsed2Port() const
{
	return this->used2Port;
}