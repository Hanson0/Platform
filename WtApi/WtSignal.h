#pragma once

using namespace System;

namespace AILinkFactoryAuto {
	namespace Instrument {
		namespace WtApi {
			public enum class WtSignal
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
		}
	}
}