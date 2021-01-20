#ifndef __WT_DUTBASE_H__
#define __WT_DUTBASE_H__

#include "Signal.h"

typedef enum
{
	WT_DUT_GENERICITY,					//Ĭ��ͨ������
	WT_DUT_WIFI_2G,						//2.4G
	WT_DUT_WIFI_5G,						//5.8G
	WT_DUT_BT,							//����
	WT_DUT_ZIGBEE,						//Zigbee
	WT_DUT_CW,							//CW
	WT_DUT_LoRa,						//LORA
	WT_DUT_Lrwpan						//LRWPAN
}enum_InsertType;

//DUT��������ģʽ
typedef enum
{
	TX_MODE_FREQ_CAL,					//����ģʽΪƵƫУ׼
	TX_MODE_POWER_CAL,					//����ģʽΪ����У׼
	TX_MODE_TX_VERIFY,					//����ģʽΪTX����
	TX_MODE_COMMON,						//ͨ�÷���ģʽ
	TX_MODE_POWER_AND_FREQ_CAL,			//����ƵƫͬʱУ׼
	TX_MODE_CAL_LOSS					//����ģʽΪ���У�߲���
}enum_TXType;

typedef enum{
	eumMacIdx_Wifi=0,					//WIFI 2.4G
	eumMacIdx_Lan=1,					//LAN
	eumMacIdx_Wan=2,					//WAN
	eumMacIdx_Wifi_5G=3,				//WIFI 5.8G
	eumMacIdx_Bt=4,						//����
	eumMacIdx_Wan0_1=5,					//WAN
	eumMacIdx_Wan0_2=6,					//WAN
	eumMacIdx_Wan0_3=7,					//WAN
	eumMacIdx_Wan0_4=8,					//WAN
	eumMacIdx_Wan1_1=9,					//WAN
	eumMacIdx_Wan1_2=10,				//WAN
	eumMacIdx_Wan1_3=11,				//WAN
	eumMacIdx_Wan1_4=12,				//WAN
	eumMacIdx_Ex0=13,					//Ԥ��ö��
	eumMacIdx_Ex1=14,					//Ԥ��ö��
	eumMacIdx_MaxCount,					//mac����
}enum_macType;


//RX���Խ��
struct stRxResult
{
	double ber;							//������
	int bitCnt;							//������
	int frameCnt;						//�հ���
	int rssi;							//���չ���
	stRxResult()
	{
		bitCnt = 0;
		ber = 0;
		frameCnt = 0;
		rssi = 0;
	}
};


#endif
