#pragma once

namespace AILinkFactoryAuto {
	namespace Instrument {
		namespace WtApi {

			public enum class WtDemo
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
		}
	}
}