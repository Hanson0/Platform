#ifndef __WT_DUTBASE_H__
#define __WT_DUTBASE_H__

#include "Signal.h"

typedef enum
{
	WT_DUT_GENERICITY,					//默认通用类型
	WT_DUT_WIFI_2G,						//2.4G
	WT_DUT_WIFI_5G,						//5.8G
	WT_DUT_BT,							//蓝牙
	WT_DUT_ZIGBEE,						//Zigbee
	WT_DUT_CW,							//CW
	WT_DUT_LoRa,						//LORA
	WT_DUT_Lrwpan						//LRWPAN
}enum_InsertType;

//DUT发送数据模式
typedef enum
{
	TX_MODE_FREQ_CAL,					//发送模式为频偏校准
	TX_MODE_POWER_CAL,					//发送模式为功率校准
	TX_MODE_TX_VERIFY,					//发送模式为TX测试
	TX_MODE_COMMON,						//通用发送模式
	TX_MODE_POWER_AND_FREQ_CAL,			//功率频偏同时校准
	TX_MODE_CAL_LOSS					//发送模式为金机校线测试
}enum_TXType;

typedef enum{
	eumMacIdx_Wifi=0,					//WIFI 2.4G
	eumMacIdx_Lan=1,					//LAN
	eumMacIdx_Wan=2,					//WAN
	eumMacIdx_Wifi_5G=3,				//WIFI 5.8G
	eumMacIdx_Bt=4,						//蓝牙
	eumMacIdx_Wan0_1=5,					//WAN
	eumMacIdx_Wan0_2=6,					//WAN
	eumMacIdx_Wan0_3=7,					//WAN
	eumMacIdx_Wan0_4=8,					//WAN
	eumMacIdx_Wan1_1=9,					//WAN
	eumMacIdx_Wan1_2=10,				//WAN
	eumMacIdx_Wan1_3=11,				//WAN
	eumMacIdx_Wan1_4=12,				//WAN
	eumMacIdx_Ex0=13,					//预留枚举
	eumMacIdx_Ex1=14,					//预留枚举
	eumMacIdx_MaxCount,					//mac总数
}enum_macType;


//RX测试结果
struct stRxResult
{
	double ber;							//误码率
	int bitCnt;							//比特数
	int frameCnt;						//收包数
	int rssi;							//接收功率
	stRxResult()
	{
		bitCnt = 0;
		ber = 0;
		frameCnt = 0;
		rssi = 0;
	}
};


#endif
