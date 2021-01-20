#ifndef __Analyse_Define__
#define __Analyse_Define__

//*****************************************************************************
//
//                         Enumerations
//
//*****************************************************************************

// Enumeration for PASS/FAIL values.
enum WT_PF_ENUM
{
	// Measurement failed.
	WT_PF_FAIL,
	// Measurement passed.
	WT_PF_PASS,
	// Pass/fail status is undefined.
	WT_PF_UNDEFINED
};
#ifndef WT300
// Enumeration for trigger selection - 802.11 a/b/g setting.
enum WT_TRIG_TYPE_ENUM
{
	// Free running ADC sampling.
	WT_TRIG_TYPE_FREE_RUN,
	// ADC External Trigger selected.
	WT_TRIG_TYPE_EXT,
	// ADC IF Trigger selected - trigger calibration will be performed.
	WT_TRIG_TYPE_IF,
	WT_TRIG_TYPE_IF_NO_CAL
};
#endif
// Enumeration for phase correction mode - 802.11 a/g setting.
enum WT_PH_CORR_ENUM
{
	// Phase correction off.
	WT_PH_CORR_OFF        = 1,
	// Symbol-by-symbol correction.  - Default value.
	WT_PH_CORR_SYM_BY_SYM = 2,
	// Moving avg. correction  - 10 symbols
	WT_PH_CORR_MOVING_AVG = 3
};

// Enumeration for phase correction mode - 802.11 b setting.
enum WT_PH_CORR_11b_ENUM
{
	// Phase correction off.
	WT_PH_CORR_11b_OFF = 1,
	// Symbol-by-symbol correction. - Default value.
	WT_PH_CORR_11b_ON  = 2,
};

// Enumeration for channel estimate - 802.11 a/g setting.
enum WT_CH_EST_ENUM
{
	// Raw Channel Estimate - long train. - Default value.
	WT_CH_EST_RAW       = 1,
	// Same as WT_CH_EST_RAW.
	WT_CH_EST_RAW_LONG  = WT_CH_EST_RAW,
	// 2nd Order Polyfit.
	WT_CH_EST_2ND_ORDER = 2,
	// Raw Channel Estimate - full packet
	WT_CH_EST_RAW_FULL  = 3
};

// Enumeration for Symbol Timing Correction - 802.11 a/g setting.
enum WT_SYM_TIM_ENUM
{
	// Symbol Timing Correction Off.
	WT_SYM_TIM_OFF = 1,
	// Symbol Timing Correction On - Default value.
	WT_SYM_TIM_ON  = 2
};

// Enumeration for Frequency Sync. Mode - 802.11 a/g setting.
enum WT_FREQ_SYNC_ENUM
{
	// Short Training Symbol.
	WT_FREQ_SYNC_SHORT_TRAIN = 1,
	// Long Training Symbol  - Default value.
	WT_FREQ_SYNC_LONG_TRAIN  = 2,
	// Full Data Packet.
	WT_FREQ_SYNC_FULL_PACKET = 3
};

// Enumeration for Amplitude Tracking - 802.11 a/g setting.
enum WT_AMPL_TRACK_ENUM
{
	// Amplitude tracking off.  - Default value.
	WT_AMPL_TRACK_OFF = 1,
	// Amplitude tracking on
	WT_AMPL_TRACK_ON  = 2
};

// Enumeration for 802.11 b method - 802.11 b setting.
enum WT_11B_METHOD_ENUM
{
	// Use 11b standard TX accuracy - Default value.
	WT_11B_STANDARD_TX_ACC      = 1,
	// Use 11b RMS error vector.
	WT_11B_RMS_ERROR_VECTOR     = 2,
	//Use 11b Std 2007 TX accuracy
	WT_11B_STANDARD_2007_TX_ACC = 3
};

// Enumeration for Number of equalizer taps - 802.11 b setting.
enum WT_EQ_ENUM
{
	// Equalizer Off. - Default value.
	WT_EQ_OFF    = 1,
	// 5 taps equalizer
	WT_EQ_5_TAPS = 5,
	// 7 taps equalizer.
	WT_EQ_7_TAPS = 7,
	// 9 taps equalizer.
	WT_EQ_9_TAPS = 9
};

// Enumeration for DC removal - 802.11 b setting.
enum WT_DC_REMOVAL_ENUM
{
	// DC removal Off  - Default value.
	WT_DC_REMOVAL_OFF = 0,
	// DC removal On.
	WT_DC_REMOVAL_ON  = 1
};

// Enumeration for enabling and disabling the RF.
enum WT_RF_ENABLE_ENUM
{
	// RF has been disabled.
	WT_RF_DISABLED,
	// RF has been enabled.
	WT_RF_ENABLED
};

// Enumeration for RF N-connector port selection.
enum WT_PORT_ENUM
{
	// Port has been disabled.
	WT_PORT_OFF = 1,
	// RF port 1
	WT_PORT_RF1 = 2,
	// RF port 2
	WT_PORT_RF2 = 3,
	// RF port 3, WT208 only
	WT_PORT_RF3 = 4,
	// RF port 4, WT208 only
	WT_PORT_RF4 = 5,

	// RF port 5, WT208C only
	WT_PORT_RF5 = 6,
	// RF port 6, WT208C only
	WT_PORT_RF6 = 7,
	// RF port 7, WT208C only
	WT_PORT_RF7 = 8,
	// RF port 8, WT208C only
	WT_PORT_RF8 = 9,

	WT_PORT_MAX
};

// Enumeration for data capture handling.
enum WT_DC_ENUM
{
	// Arm the WT160 tester for new data capture.
	WT_DC_ARM_NEW,
	// Auto Range Process.
	IQV_DC_ARM_AUTORANGE,
	// Undefined default value.
	WT_DC_UNDEFINED
};

// Enumeration for enabling and disabling swapping of I and Q signals.
enum WT_IQ_SWAP_ENUM
{
	// IQ swap has been disabled.  -default
	WT_IQ_SWAP_DISABLED,
	// IQ swap has been enabled.
	WT_IQ_SWAP_ENABLED
};

//Enumeration for enabling and disabling reversion of I and Q signals.
enum WT_IQ_Reversion_ENUM
{
	// - Default value.
	WT_IQ_IQReversion_DISABLED,
	WT_IQ_IReversion_ENABLED,
	WT_IQ_QReversion_ENABLED,
	WT_IQ_IQReversion_ENABLED
};

enum WT_ZB_ANALYSIS_OPTIMISE_ENUM
{
	WT_ZB_ANALYSIS_OPTIMISE_DISABLED,
	WT_ZB_ANALYSIS_OPTIMISE_ENABLED,
};

//Enumeration for frame bandwidth dectecting.
enum WT_BANDWIDTH_DETECT_ENUM
{
	// - Default value.
	WT_USER_DEFINED,
	WT_BW_AUTO_DETECT,
	WT_AUTO_DETECT
};

enum WT_DEMOD_ENUM
{
	// 11a/g
	WT_DEMOD_11AG,
	// 11b
	WT_DEMOD_11B,
	// 11n 20M
	WT_DEMOD_11N_20M,
	// 11n 40M
	WT_DEMOD_11N_40M,
	// 11ac 20M
	WT_DEMOD_11AC_20M,
	// 11ac 40M
	WT_DEMOD_11AC_40M,
	// 11ac 80M
	WT_DEMOD_11AC_80M,
	// 11ac 160M
	WT_DEMOD_11AC_160M,
	// 11ac 80+80M
	WT_DEMOD_11AC_80_80M,
	// Bluetooth
	WT_DEMOD_BT,
	// Zigbee
	WT_DEMOD_ZIGBEE,
	// 11ah 1M
	WT_DEMOD_11AH_1M,
	// 11ah 2M
	WT_DEMOD_11AH_2M,
	// 11ah 4M
	WT_DEMOD_11AH_4M,
	// 11ah 8M
	WT_DEMOD_11AH_8M,
	// 11ah 16M
	WT_DEMOD_11AH_16M,

	//ContinuesWave
	WT_DEMOD_CW,

	//11p
	WT_DEMOD_11P_5M,
	WT_DEMOD_11P_10M,

	//lora
	WT_DEMOD_LORA_125K,
	WT_DEMOD_LORA_250K,
	WT_DEMOD_LORA_500K,
	
	// 11ax 20M
	WT_DEMOD_11AX_20M,
	// 11ax 40M
	WT_DEMOD_11AX_40M,
	// 11ax 80M
	WT_DEMOD_11AX_80M,
	// 11ax 160M
	WT_DEMOD_11AX_160M,
	// 11ax 80+80M
	WT_DEMOD_11AX_80_80M,

	//802.15.4g
	WT_DEMOD_LRWPAN_FSK,
	WT_DEMOD_LRWPAN_OQPSK,
	WT_DEMOD_LRWPAN_OFDM,
	
	//ZWave
	WT_DEMOD_ZWAVE,
	//NB-IOT
	WT_DEMOD_NBIOT_NPUSCH,
	WT_DEMOD_NBIOT_NPRACH,
	// Unknow
	WT_DEMOD_UNKNOW = 0xFF
};

//*****************************************************************************
//
// The following are the signals, which are predefined for use with the tester.
//
//*****************************************************************************
enum WT_SIGNAL_ENUM
{
	// Wave file Defined by user.
	SIG_USERFILE,

	// Continuous Wave.
	SIG_CW_SIN0,
	// Continuous Wave Sin 100KHz.
	SIG_CW_SIN100K,
	// Continuous Wave Sin 1MHZ.
	SIG_CW_SIN1M,
	// Continuous Wave Sin -100KHZ.
	SIG_CW_SINNEG100K,

	// 802.11g  6 Mbit/s.
	SIG_802_11_G_6MBS = 101,
	// 802.11g  9 Mbit/s.
	SIG_802_11_G_9MBS,
	// 802.11g 12 Mbit/s.
	SIG_802_11_G_12MBS,
	// 802.11g 18 Mbit/s.
	SIG_802_11_G_18MBS,
	// 802.11g 24 Mbit/s.
	SIG_802_11_G_24MBS,
	// 802.11g 36 Mbit/s.
	SIG_802_11_G_36MBS,
	// 802.11g 48 Mbit/s.
	SIG_802_11_G_48MBS,
	// 802.11g 54 Mbit/s.
	SIG_802_11_G_54MBS,

	// 802.11n 20M MCS0.
	SIG_HT_20_MCS0 = 201,
	// 802.11n 20M MCS1.
	SIG_HT_20_MCS1,
	// 802.11n 20M MCS2.
	SIG_HT_20_MCS2,
	// 802.11n 20M MCS3.
	SIG_HT_20_MCS3,
	// 802.11n 20M MCS4.
	SIG_HT_20_MCS4,
	// 802.11n 20M MCS5.
	SIG_HT_20_MCS5,
	// 802.11n 20M MCS6.
	SIG_HT_20_MCS6,
	// 802.11n 20M MCS7.
	SIG_HT_20_MCS7,

	// 802.11n 40M MCS0.
	SIG_HT_40_MCS0 = 301,
	// 802.11n 40M MCS1.
	SIG_HT_40_MCS1,
	// 802.11n 40M MCS2.
	SIG_HT_40_MCS2,
	// 802.11n 40M MCS3.
	SIG_HT_40_MCS3,
	// 802.11n 40M MCS4.
	SIG_HT_40_MCS4,
	// 802.11n 40M MCS5.
	SIG_HT_40_MCS5,
	// 802.11n 40M MCS6.
	SIG_HT_40_MCS6,
	// 802.11n 40M MCS7.
	SIG_HT_40_MCS7,

	// 802.11ac 20M MCS0.
	SIG_VHT_20_MCS0 = 401,
	// 802.11ac 20M MCS1.
	SIG_VHT_20_MCS1,
	// 802.11ac 20M MCS2.
	SIG_VHT_20_MCS2,
	// 802.11ac 20M MCS3.
	SIG_VHT_20_MCS3,
	// 802.11ac 20M MCS4.
	SIG_VHT_20_MCS4,
	// 802.11ac 20M MCS5.
	SIG_VHT_20_MCS5,
	// 802.11ac 20M MCS6.
	SIG_VHT_20_MCS6,
	// 802.11ac 20M MCS7.
	SIG_VHT_20_MCS7,
	// 802.11ac 20M MCS8.
	SIG_VHT_20_MCS8,

	// 802.11ac 40M MCS0.
	SIG_VHT_40_MCS0 = 501,
	// 802.11ac 40M MCS1.
	SIG_VHT_40_MCS1,
	// 802.11ac 40M MCS2.
	SIG_VHT_40_MCS2,
	// 802.11ac 40M MCS3.
	SIG_VHT_40_MCS3,
	// 802.11ac 40M MCS4.
	SIG_VHT_40_MCS4,
	// 802.11ac 40M MCS5.
	SIG_VHT_40_MCS5,
	// 802.11ac 40M MCS6.
	SIG_VHT_40_MCS6,
	// 802.11ac 40M MCS7.
	SIG_VHT_40_MCS7,
	// 802.11ac 40M MCS8.
	SIG_VHT_40_MCS8,
	// 802.11ac 40M MCS9.
	SIG_VHT_40_MCS9,

	// 802.11ac 80M MCS0.
	SIG_VHT_80_MCS0 = 601,
	// 802.11ac 80M MCS1.
	SIG_VHT_80_MCS1,
	// 802.11ac 80M MCS2.
	SIG_VHT_80_MCS2,
	// 802.11ac 80M MCS3.
	SIG_VHT_80_MCS3,
	// 802.11ac 80M MCS4.
	SIG_VHT_80_MCS4,
	// 802.11ac 80M MCS5.
	SIG_VHT_80_MCS5,
	// 802.11ac 80M MCS6.
	SIG_VHT_80_MCS6,
	// 802.11ac 80M MCS7.
	SIG_VHT_80_MCS7,
	// 802.11ac 80M MCS8.
	SIG_VHT_80_MCS8,
	// 802.11ac 80M MCS9.
	SIG_VHT_80_MCS9,

	// 802.11b 1 Mbit/s.
	SIG_802_11_B_1MBS = 701,
	// 802.11b 2 Mbit/s.
	SIG_802_11_B_2MBS,
	// 802.11b 5.5 Mbit/s.
	SIG_802_11_B_5_5MBS,
	// 802.11b 11 Mbit/s.
	SIG_802_11_B_11MBS,

	//*** Begined with FW version 3.0.1.4 ***

	// 802.11n 20M MCS0 ShortGI.
	SIG_HT_20_MCS0_ShortGI = 1201,
	// 802.11n 20M MCS1 ShortGI.
	SIG_HT_20_MCS1_ShortGI,
	// 802.11n 20M MCS2 ShortGI.
	SIG_HT_20_MCS2_ShortGI,
	// 802.11n 20M MCS3 ShortGI.
	SIG_HT_20_MCS3_ShortGI,
	// 802.11n 20M MCS4 ShortGI.
	SIG_HT_20_MCS4_ShortGI,
	// 802.11n 20M MCS5 ShortGI.
	SIG_HT_20_MCS5_ShortGI,
	// 802.11n 20M MCS6 ShortGI.
	SIG_HT_20_MCS6_ShortGI,
	// 802.11n 20M MCS7 ShortGI.
	SIG_HT_20_MCS7_ShortGI,

	// 802.11n 40M MCS0 ShortGI.
	SIG_HT_40_MCS0_ShortGI = 1301,
	// 802.11n 40M MCS1 ShortGI.
	SIG_HT_40_MCS1_ShortGI,
	// 802.11n 40M MCS2 ShortGI.
	SIG_HT_40_MCS2_ShortGI,
	// 802.11n 40M MCS3 ShortGI.
	SIG_HT_40_MCS3_ShortGI,
	// 802.11n 40M MCS4 ShortGI.
	SIG_HT_40_MCS4_ShortGI,
	// 802.11n 40M MCS5 ShortGI.
	SIG_HT_40_MCS5_ShortGI,
	// 802.11n 40M MCS6 ShortGI.
	SIG_HT_40_MCS6_ShortGI,
	// 802.11n 40M MCS7 ShortGI.
	SIG_HT_40_MCS7_ShortGI,

	// 802.11ac 20M MCS0 ShortGI.
	SIG_VHT_20_MCS0_ShortGI = 1401,
	// 802.11ac 20M MCS1 ShortGI.
	SIG_VHT_20_MCS1_ShortGI,
	// 802.11ac 20M MCS2 ShortGI.
	SIG_VHT_20_MCS2_ShortGI,
	// 802.11ac 20M MCS3 ShortGI.
	SIG_VHT_20_MCS3_ShortGI,
	// 802.11ac 20M MCS4 ShortGI.
	SIG_VHT_20_MCS4_ShortGI,
	// 802.11ac 20M MCS5 ShortGI.
	SIG_VHT_20_MCS5_ShortGI,
	// 802.11ac 20M MCS6 ShortGI.
	SIG_VHT_20_MCS6_ShortGI,
	// 802.11ac 20M MCS7 ShortGI.
	SIG_VHT_20_MCS7_ShortGI,
	// 802.11ac 20M MCS8 ShortGI.
	SIG_VHT_20_MCS8_ShortGI,

	// 802.11ac 40M MCS0 ShortGI.
	SIG_VHT_40_MCS0_ShortGI = 1501,
	// 802.11ac 40M MCS1 ShortGI.
	SIG_VHT_40_MCS1_ShortGI,
	// 802.11ac 40M MCS2 ShortGI.
	SIG_VHT_40_MCS2_ShortGI,
	// 802.11ac 40M MCS3 ShortGI.
	SIG_VHT_40_MCS3_ShortGI,
	// 802.11ac 40M MCS4 ShortGI.
	SIG_VHT_40_MCS4_ShortGI,
	// 802.11ac 40M MCS5 ShortGI.
	SIG_VHT_40_MCS5_ShortGI,
	// 802.11ac 40M MCS6 ShortGI.
	SIG_VHT_40_MCS6_ShortGI,
	// 802.11ac 40M MCS7 ShortGI.
	SIG_VHT_40_MCS7_ShortGI,
	// 802.11ac 40M MCS8 ShortGI.
	SIG_VHT_40_MCS8_ShortGI,
	// 802.11ac 40M MCS9 ShortGI.
	SIG_VHT_40_MCS9_ShortGI,

	// 802.11ac 80M MCS0 ShortGI.
	SIG_VHT_80_MCS0_ShortGI = 1601,
	// 802.11ac 80M MCS1 ShortGI.
	SIG_VHT_80_MCS1_ShortGI,
	// 802.11ac 80M MCS2 ShortGI.
	SIG_VHT_80_MCS2_ShortGI,
	// 802.11ac 80M MCS3 ShortGI.
	SIG_VHT_80_MCS3_ShortGI,
	// 802.11ac 80M MCS4 ShortGI.
	SIG_VHT_80_MCS4_ShortGI,
	// 802.11ac 80M MCS5 ShortGI.
	SIG_VHT_80_MCS5_ShortGI,
	// 802.11ac 80M MCS6 ShortGI.
	SIG_VHT_80_MCS6_ShortGI,
	// 802.11ac 80M MCS7 ShortGI.
	SIG_VHT_80_MCS7_ShortGI,
	// 802.11ac 80M MCS8 ShortGI.
	SIG_VHT_80_MCS8_ShortGI,
	// 802.11ac 80M MCS9 ShortGI.
	SIG_VHT_80_MCS9_ShortGI,

	// 802.11b 1 Mbit/s Short Preamble. Invalid.
	SIG_802_11_B_1MBS_ShortPreamble = 1701,
	// 802.11b 2 Mbit/s   Short Preamble.
	SIG_802_11_B_2MBS_ShortPreamble,
	// 802.11b 5.5 Mbit/s Short Preamble.
	SIG_802_11_B_5_5MBS_ShortPreamble,
	// 802.11b 11 Mbit/s  Short Preamble.
	SIG_802_11_B_11MBS_ShortPreamble,

	//GPS
	SIG_GPS_SIGNAL = 2000,

    //BDS
	SIG_BDS_SIGNAL = 3000,

	// Wave file Defined by Tester.					  
	SIG_TESTERFILE = 5000,


	SIG_LAST
};

// Enumeration for signal modulation source.
enum WT_SOURCE_ENUM
{
	// Internal modulation from wave.
	WT_SOURCE_WAVE,
	// Internal modulation from signal generator.
	WT_SOURCE_SIGNAL_GENERATOR,
	// Undefined default modulation source.
	WT_SOURCE_UNDEFINED
};

// Enumeration for Reference Clock.
enum WT_REF_CLK_ENUM
{
	// Auto.
	WT_CLK_AUTO,
	// External Reference Clock.
	WT_CLK_EXT,
	// Internal Reference Clock.
	WT_CLK_INT
};

// Enumeration for Operating Type, WT-208 only.
enum WT_OPERTATE_ENUM
{
	// - Default value.
	WT_OPERTATE_GLOBAL,
	WT_OPERTATE_RX,
	WT_OPERTATE_TX
};

//Enumeration for BT DataRate.
enum WT_BT_DATARATE
{
	WT_BT_DATARATE_Auto = 0,
	WT_BT_DATARATE_1M   = 1,
	WT_BT_DATARATE_2M   = 2,
	WT_BT_DATARATE_3M   = 3,
	WT_BT_BLE = 4,
	WT_BT_BLE_1M = 4, 
	WT_BT_BLE_2M = 5,
	WT_BT_BLE_125K = 6,
	WT_BT_BLE_500K = 7,

	WT_BT_UNKNOWN = 100
};

//Enumeration for BT Packet type.
enum WT_BT_PACKETTYPE
{
	WT_BT_PACKETTYPE_NULL  = 0,
	WT_BT_PACKETTYPE_POLL  = 1,
	WT_BT_PACKETTYPE_FHS   = 2,
	WT_BT_PACKETTYPE_DH1   = 3,
	WT_BT_PACKETTYPE_DH3   = 4,
	WT_BT_PACKETTYPE_DH5   = 5,
	WT_BT_PACKETTYPE_DM1   = 6,
	WT_BT_PACKETTYPE_DM3   = 7,
	WT_BT_PACKETTYPE_DM5   = 8,
	WT_BT_PACKETTYPE_HV1   = 9,
	WT_BT_PACKETTYPE_HV2   = 10,
	WT_BT_PACKETTYPE_HV3   = 11,
	WT_BT_PACKETTYPE_DV    = 12,
	WT_BT_PACKETTYPE_AUX1  = 13,
	WT_BT_PACKETTYPE_EV3   = 14,
	WT_BT_PACKETTYPE_EV4   = 15,
	WT_BT_PACKETTYPE_EV5   = 16,
	WT_BT_PACKETTYPE_2_DH1 = 17,
	WT_BT_PACKETTYPE_2_DH3 = 18,
	WT_BT_PACKETTYPE_2_DH5 = 19,
	WT_BT_PACKETTYPE_3_DH1 = 20,
	WT_BT_PACKETTYPE_3_DH3 = 21,
	WT_BT_PACKETTYPE_3_DH5 = 22,
	WT_BT_PACKETTYPE_2_EV3 = 23,
	WT_BT_PACKETTYPE_2_EV5 = 24,
	WT_BT_PACKETTYPE_3_EV3 = 25,
	WT_BT_PACKETTYPE_3_EV5 = 26
};

enum WT_STANDARD_ENUM
{
	IEEE802_11_a_g_OFDM,
	IEEE802_11_b_g_DSSS,
	IEEE802_11_n,
	IEEE802_11_ac,
	Bluetooth,
	IEEE_Zigbee,
	ContinuousWaves,
	IEEE802_11_ax,
	ZWave,
	StandardCount
};

enum DATARATE_11A_ENUM
{
	//OFDM
	Mbps54 = 0,
	Mbps48,
	Mbps36,
	Mbps24,
	Mbps18,
	Mbps12,
	Mbps9,
	Mbps6
};

enum DATARATE_11B_ENUM
{
	//DSSS
	Mbps11 = 100,
	Mbps5point5,
	Mbps2,
	Mbps1
};

enum HT_FRAME_TYPE_ENUM
{
	FRM_HT_MF = 1,
	FRM_HT_GF
};


enum PSDU_TYPE_ENUM
{
	PSDUType_ALL0 = 1,
	PSDUType_ALL1,
	PSDUType_ALT01,
	PSDUType_RANDOM,
	PSDUType_PRBS9,
	PSDUType_PRBS15,
};

enum WT_RESULT_DATA_TYPE
{
	//1字节
	TYPE_int8,
	//2字节
	TYPE_int16,
	//4字节
	TYPE_int32,
	//8字节
	TYPE_double,
	//16字节
	TYPE_complex,

    TYPE_struct
};

enum PREAMBLE_TYPE
{
	PRE_LONG_11B,
	PRE_SHORT_11B
};

enum ZWAVE_RATE_ENUM
{
    ZWAVE_R1 = 1,
    ZWAVE_R2 = 2,
    ZWAVE_R3 = 3
};

enum TERSTER_WAVE_OPERATE_OPTION
{
	//添加信号数据
	ADD_WAVE,
	//删除信号
	REMOVE_WAVE
};

enum TESTER_SAMPLERATE_MODE
{
	//采样率默认模式,采样率设为120M
	RATE_DEFAULT,
	RATE_15M,
	RATE_30M,
	RATE_60M,
	//采样率自动匹配模式,采样率根据标准和带宽匹配最佳采样率
	RATE_AUTO
};

enum SYMBOLS_EVM_RESULT_TYPE
{
	//取平均值
	AVERAGE_VALUE,
	//取最大值
	MAX_VALUE,
	//取最小值
	MIN_VALUE
};

enum iBEAFORMING_CHIP_ENUM
{
	iBEAFORMING_INIT_ENUM = 0,
	//For BCM Implicit Beamforming
	iBEAFORMING_BCM_STATE_1 = 1,
	iBEAFORMING_BCM_STATE_2,
	//For MTK Implicit Beamforming
	iBEAFORMING_MTK_STATE_1 = 10,
	iBEAFORMING_MTK_STATE_2
};

enum SPECTRUM_MASK_VERSION
{
	Ieee2009,
	Ieee2012
};

enum NB_IOT_NPRACH_FORMAT
{
	PREAMBLE_FORMAT0 = 0,
	PREAMBLE_FORMAT1 = 1,
	PREAMBLE_FORMAT_END
};

enum NB_IOT_NPUSCH_FORMAT
{
	NPUSCH_FORMAT1 = 1,
	NPUSCH_FORMAT2 = 2,
	NPUSCH_FORMAT_END
};
enum NB_IOT_NPUSCH_TONE
{
	NPUSCH_SINGLE_TONE = 1,
	NPUSCH_MULTI_TONE3 = 3,
	NPUSCH_MULTI_TONE6 = 6,
	NPUSCH_MULTI_TONE12 = 12,
	NPUSCH_TONE_END
};
enum NB_IOT_SUBCARRIER_DETA_FREQ
{
	NPUSCH_DETA_F_3750_HZ = 3750,
	NPUSCH_DETA_F_15000_HZ = 15000,
	NPUSCH_DETA_F_END
};
enum NB_IOT_NPUSCH_QM
{
	NPUSCH_BPSK = 1,
	NPUSCH_QPSK = 2,
};
// 设备规格结构体,用于200/200B/208的license规格获取
typedef struct
{
	char lic_5g;                         // 是否支持5G：1支持；其他不支持
	char lic_ac;                         // 是否支持ac测试
	char lic_bluetooth;                  // 是否支持BT测试
	char lic_mimo;                       // 是否支持MIMO测试
	char lic_zigbee;                     // 是否支持Zigbee测试
	char lic_gps;                        // 是否支持GPS测试
	char lic_2g4;                        // 是否支持2.4g测试
	char lic_cmimo;                      // 是否支持Composite MIMO测试
	char lic_switched_mimo;              // 是否支持Switched MIMO测试
	char lic_ac80_80;                    // 是否支持AC80+80测试
	char no_use[4];                      // 无用
	char lic_11p;                        // 是否支持11p测试
	char lic_2g3_2g7;                    // 是否支持2.3-2.7G频段
	char temp[48];                       // 保留位
} DeviceSpecification;

// 208C设备规格结构体
typedef struct
{
	char lic_base;                       // 是否支持lic_base测试
	char lic_4port;                      // 是否支持RF Port3/4测试
	char lic_8port;                      // 是否支持RF Port5/6/7/8测试，依赖于lic_4port
	char lic_wtl_2g4;                    // 是否支持11a/b/g/n 2.4G频段测试
	char lic_wtl_5g;                     // 是否支持11a/b/g/n 5G测试，依赖于lic_wtl_2g4
	char lic_wtl_ac;                     // 是否支持11ac测试，依赖于lic_wtl_5g
	char lic_wtl_mimo;                   // 是否支持True MIMO测试，依赖于lic_wtl_2g4
	char lic_wtl_bt;                     // 是否支持BT测试
	char lic_wtl_zigbee;                 // 是否支持ZigBee测试
	char lic_wtl_11p;                    // 是否支持11p测试
	char lic_wtl_11ah;                   // 是否支持11ah测试
	char lic_wtl_gps;                    // 是否支持gps测试
	char lic_wtl_lora;                   // 是否支持LoRa测试
	char lic_wtl_dect;                   // 是否支持DECT测试
	char lic_wtl_bds;                    // 是否支持BDS测试
	char lic_wtl_z_wave;                 // 是否支持Z-Wave测试
	char lic_2g5_3g8;                    // 是否支持2.5g-3.8g的测试
	char lic_wtl_nbiot;                  // 是否支持nbiot的测试
	char lic_wtl_wisun;					 // 是否支持wisun的测试，即LRWPAN测试
	char temp[45];                       // 保留位
}Device208CSpecification;

//*****************************************************************************
//
//                   Enumerations only for WT-208
//
//*****************************************************************************
typedef struct
{
	//*****************************************************************************
	//                            基础配置，该部分必须配置
	//*****************************************************************************

	char VirAddr1[16];                       // 虚拟IP 1
	char VirAddr2[16];                       // 虚拟IP 2
	char VirAddr3[16];                       // 虚拟IP 3
	char VirAddr4[16];                       // 虚拟IP 4
	char DutAddr[16];                        // DUT IP,必须与仪器IP不在同一网段

	//*****************************************************************************
	//                           DUT作为TFTP Server部分
	//
	//      无TFTP需求时，以下IP都设置为空
	//
	//      需配置DUT在TFTP状态下指定的Server IP
	//*****************************************************************************
	char DutTftpServerAddr[16];             // DUT在TFTP状态下指定的Server IP

	//*****************************************************************************
	//                           FFTP部分
	//
	//      无TFTP需求时，以下IP都设置为空
	//
	//      当PC作为TFTP Server时，需配置实际作为Server的PC IP
	//      还需配置DUT在TFTP状态下所使用的Client IP以及DUT所指定的Server IP
	//*****************************************************************************
	char TftpServerAddr[16];                 // DUT在TFTP状态下所指定的Server IP
	char TftpClientAddr[16];                 // DUT在TFTP状态下所使用的Client IP,必须与TftpServerAddr不一样
	char TftpServerPCAddr[16];               // PC作为TFTP Server时实际PC IP,需确保该IP与DUT的虚拟IP在同一网络下

} WT_208_NET_TYPE;

//*****************************************************************************
//
//                   Enumerations only for Virtual Subnet
//
//*****************************************************************************
#define MAX_SUB_NET_COUNT   8
typedef struct
{
	//*****************************************************************************
	//                            基础配置，该部分必须配置
	//*****************************************************************************

	char VirAddr[MAX_SUB_NET_COUNT][16];                         // 虚拟IP,最多8个子网口，依次对应1~8子网口。不需要配置的子网口赋值为NULL
	char DutAddr[16];                        // DUT IP,必须与仪器IP不在同一网段

	//*****************************************************************************
	//                           DUT作为TFTP Server部分
	//
	//      无TFTP需求时，以下IP都设置为空
	//
	//      需配置DUT在TFTP状态下指定的Server IP
	//*****************************************************************************
	char DutTftpServerAddr[16];             // DUT在TFTP状态下指定的Server IP

	//*****************************************************************************
	//                           FFTP部分
	//
	//      无TFTP需求时，以下IP都设置为空
	//
	//      当PC作为TFTP Server时，需配置实际作为Server的PC IP
	//      还需配置DUT在TFTP状态下所使用的Client IP以及DUT所指定的Server IP
	//*****************************************************************************
	char TftpServerAddr[16];                 // DUT在TFTP状态下所指定的Server IP
	char TftpClientAddr[16];                 // DUT在TFTP状态下所使用的Client IP,必须与TftpServerAddr不一样
	char TftpServerPCAddr[16];               // PC作为TFTP Server时实际PC IP,需确保该IP与DUT的虚拟IP在同一网络下

} WT_VIRTUAL_NET_TYPE;

typedef struct
{
	enum WT_PORT_ENUM port;
	int valid;
} SW_MIMO_Ant;

#define MAX_PORT_COUNT 8

typedef struct
{
	SW_MIMO_Ant VSA_Port[MAX_PORT_COUNT];
} WT_SW_MIMO_Ant;

typedef struct
{
    int mrFskType;
    int mrFskDataRate;
    int mrFskSfdEnable;
    int phyMrFskFecEnable;
    int phyMrFskSfdValue;
    double fskModIndex;
}LrwpanFskParam;

#endif

