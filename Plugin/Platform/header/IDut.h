#ifndef __WT_DUT_H__
#define __WT_DUT_H__

#include "DutBase.h"
#include "CallBackFunc.h"

#define DUT_PLUGIN_VERSION "1.0.0"

#ifdef DUT_EXPORTS
#define DUT_API __declspec(dllexport)
#else
#define DUT_API __declspec(dllimport)
#endif

#define DUT_FUNC extern "C" DUT_API

#define DUT_NAMESPACE DutNamespace
#define DUT_NAMESPACE_BEGIN namespace DUT_NAMESPACE {
#define DUT_NAMESPACE_END }

DUT_NAMESPACE_BEGIN
class IDut
{
public:
	virtual void SetCallBackManager(const CallBackManager &cbManager) = 0;

	virtual void SetDutId(int id) = 0;
	virtual void GetDutInfo(char *dutName, int nameSize, char *version, int versionSize) = 0;
	virtual bool Init() = 0;    
	virtual bool Terminate() = 0;

	virtual bool EnableNIC(bool value) = 0;		// true:启用网卡；false:禁用网卡
	virtual bool EnablePCIE(bool value) = 0;    // true:启用网卡；false:禁用网卡

	virtual bool IsDutReady() = 0;

	//无使用接口
	virtual void WarmUp(int time_ms) = 0; 

	//修改参数
	virtual bool Open(int type) = 0;
	virtual bool Close(int type) = 0;
	virtual bool TempCompensation(int type) = 0;
	virtual bool SetSignal(Signal *signal) = 0;
	virtual bool GetTgtPwrAndPwrReg(Signal *signal, double *targetPow, int *powReg) = 0;
	virtual bool CalBegin(int type) = 0;
	virtual bool CalEnd(int type) = 0;

	virtual int GetAntCount(int band) = 0;
	virtual bool ExecCmd(const char *cmd, const char *ack, int timeout, char *recv, int recvSize) = 0; 	

	virtual bool AdjustFreqReg(double freqErrPpm, int *regVal) = 0;
	virtual bool AdjustFreqReg_CW(double freqErrPpm, int *regVal) = 0;
	virtual bool AdjustPwrReg(double powerErr, int *regVal) = 0;
	virtual bool AdjustRxReg(long param, long reserve) = 0;

	virtual bool FineTurnPower_Reduce(int *regVal) = 0;
	virtual bool FineTurnPower_Increase(int *regVal) = 0;

	virtual bool GetFreqCalRegVal(int band, int *regVal) = 0;
	virtual bool SetFreqCalRegVal(int band, int regVal) = 0;
	virtual bool GetPwrCalRegVal(int band, int ant, int channel, int *regVal) = 0;
	virtual bool SetPwrCalRegVal(int band, int ant, int channel, int *regVal) = 0;

	virtual bool TxFrame(int txmode = TX_MODE_COMMON) = 0;
	virtual bool TxCarrier() = 0;
	virtual bool TxStop() = 0;
	virtual bool TxCarrierStop() = 0;
	virtual bool RxStart() = 0;
	virtual bool RxStop() = 0;
	virtual bool GetPerResult(stRxResult *result) = 0;

	virtual bool GetSN(char *SN, int SNSize) = 0;
	virtual bool SetMac(int macType, const char *strmac) = 0;
	virtual bool GetMac(char *mac, int macSize, int macType) = 0;

	virtual bool SaveCalData(int type) = 0;
	virtual bool WriteEfuse(int type) = 0;
	virtual bool CheckEfuse(int type) = 0;
	virtual bool GetEfuseFreeBlockNum(int *number) = 0;
	virtual bool GetEfuseTotalBlockNum(int *number) = 0;

	//数据交流接口
	virtual bool DataExchange(char *data, int dataSize) = 0;
	//保留扩展接口
	virtual bool Reserved(int type, long *reserved, int size) = 0;
};

DUT_FUNC IDut *CreatePlugin();
DUT_FUNC void DestroyPlugin(IDut *plugin);
DUT_FUNC void GetPluginVersion(char *version, int verSize);		//获取接口版本号

DUT_NAMESPACE_END

#endif
