#pragma once

using namespace System;

namespace AILinkFactoryAuto {
	namespace Instrument {
		namespace WtApi {
			public ref class WtResParamString
			{
			public:
				//*****************************************************************************
				//                            SPECTRUM
				//*****************************************************************************
				//Carrier leakage in dB.Value is returned
				static String^ WT_RES_SPECTRUM_CARR_LEAKAGE = gcnew String("Spec_carrier_leakage");

				//OBW(99%) in Hz.Value is returned
				static String^ WT_RES_SPECTRUM_OBW_99 = gcnew String("Spec_Obw");

				//Spectrum mask error point in %.Value is returned
				static String^ WT_RES_SPECTRUM_MASK_ERR_PERCENT = gcnew String("Spec_mask_err");

				//Frequency of the max power in Hz.Value is returned
				static String^ WT_RES_SPECTRUM_PEAK_POW_FREQ = gcnew String("Spec_peak_freq");

				//Spectrum data. Vector is returned.
				static String^ WT_RES_SPECTRUM_DATA = gcnew String("Spec_data");

				//Spectrum Mask Margin data. Complex Vector is returned.
				static String^ WT_RES_SPECTRUM_MARGIN = gcnew String("Spec_margin");

				//Spectrum mask. Complex Vector is returned.
				static String^ WT_RES_SPECTRUM_MASK = gcnew String("Spec_mask");

				//Frequency in Hz.Value is returned. CW only.
				static String^ WT_RES_CW_FREQ_OFFSET = gcnew String("CW_spec_freq_offset");

				//Frequency in Hz.Value is returned. Z-Wave only.
				static String^ WT_RES_Z_WAVE_FREQ_OFFSET = gcnew String("Z_wave_spec_freq_offset");

				//*****************************************************************************
				//                            IQ
				//*****************************************************************************
				//RAW data. Complex vector is returned.
				static String^ WT_RES_RAW_DATA = gcnew String("Raw_data");

				//*****************************************************************************
				//                            POWER
				//*****************************************************************************
				// Frame Count by Power Detectoring. Value is returned.
				static String^ WT_RES_POWER_FRAME_CNT = gcnew String("Pow_frame_count");

				// Power frame (no gap) in dB. Value is returned.
				static String^ WT_RES_POWER_FRAME_DB = gcnew String("Pow_frame");

				// RMS Power in dB. Value is returned.
				static String^ WT_RES_POWER_ALL_DB = gcnew String("Pow_all");

				// Power Peak in dB. Value is returned.
				static String^ WT_RES_POWER_PEAK_DB = gcnew String("Pow_peak");

				//*****************************************************************************
				//                            WIFI Frame
				//*****************************************************************************
				// EVM for entire frame in dB. Value is returned.
				static String^ WT_RES_FRAME_EVM_ALL = gcnew String("evm.all");

				// EVM for entire frame in %. Value is returned.
				static String^ WT_RES_FRAME_EVM_ALL_PERCENT = gcnew String("evm.all(%)");

				// EVM peak value in dB. Value is returned.
				static String^ WT_RES_FRAME_EVM_PEAK = gcnew String("evm.pk");

				// EVM peak value in %. Value is returned.
				static String^ WT_RES_FRAME_EVM_PEAK_PERCENT = gcnew String("evm.pk(%)");

				// Frequency Error in Hz. Value is returned.
				static String^ WT_RES_FRAME_FREQ_ERR = gcnew String("signal.freqerr");

				// Symbol Clock Error in ppm. Value is returned.
				static String^ WT_RES_FRAME_SYMBOL_CLOCK_ERR = gcnew String("signal.symclockerr");

				// IQ Match Amplitude Error in dB. Value is returned.
				static String^ WT_RES_FRAME_IQ_MATCH_AMP = gcnew String("iqmatch.amp");

				// IQ Match Phase Error in Deg. Value is returned.
				static String^ WT_RES_FRAME_IQ_MATCH_PHASE = gcnew String("iqmatch.phase");

				// IQ Phase Error in Deg. Value is returned.
				static String^ WT_RES_FRAME_PHASE_ERROR = gcnew String("phase.error");

				// Data rate in Mbps. Value is returned.
				static String^ WT_RES_FRAME_DATA_RATE_MBPS = gcnew String("Data_rate_Mbps");

				// Ramp on time. Value is returned.
				static String^ WT_RES_FRAME_RAMP_ON_TIME = gcnew String("ramp.on_time");

				// Ramp off time. Value is returned.
				static String^ WT_RES_FRAME_RAMP_OFF_TIME = gcnew String("ramp.off_time");

				// Number of symbols. Value is returned. OFDM only
				static String^ WT_RES_FRAME_OFDM_NUMBER_SYMBOLS = gcnew String("ofdm.more_res.PLCP.Nspp");

				// EVM for data part of frame.dB. Value is returned. OFDM only
				static String^ WT_RES_FRAME_EVM_DATA_DB = gcnew String("evm.data");

				// EVM for data part of frame.%. Value is returned.
				static String^ WT_RES_FRAME_EVM_DATA_PERCENT = gcnew String("evm.data(%)");

				// EVM for pilot part of frame.dB. Value is returned.
				static String^ WT_RES_FRAME_EVM_PILOT_DB = gcnew String("evm.pilot");

				// Spectral flatness Passed Or Failed. 1(1.0) - Passed; 0(0.0) - Failed. OFDM only
				static String^ WT_RES_SPECTRUM_FLATNESS_PASSED = gcnew String("flatness.passed");

				// Spectral flatness section value. Complex Vector is returned.  OFDM only
				static String^ WT_RES_SPECTRUM_FLATNESS_SECTION_VALUE = gcnew String("flatness.section.value");

				// Spectral flatness section margin. Complex Vector is returned. OFDM only
				static String^ WT_RES_SPECTRUM_FLATNESS_SECTION_MARGIN = gcnew String("flatness.section.margin");

				/*Spectrum Flatness Data. Complex Vector is returned*/
				static String^  WT_RES_OFDM_SPECTRUM_FLATNESS_DATA = gcnew String("Spec_flatness_data");

				/*Spectrum Flatness Data. Complex Vector is returned*/
				static String^  WT_RES_OFDM_SPECTRUM_FLATNESS_MASKUP_DATA = gcnew String("Spec_flatness_maskup_data");

				/*Spectrum Flatness Data. Complex Vector is returned*/
				static String^  WT_RES_OFDM_SPECTRUM_FLATNESS_MASKDOWN_DATA = gcnew String("Spec_flatness_maskdown_data");

				// IQ DC Offset For 11B in dB. Value is returned. DSSS/CCK only
				static String^ WT_RES_FRAME_IQ_OFFSET_11B = gcnew String("iq.offset");

				// RF Carrier Suppression for 11B in dB. Value is returned. DSSS/CCK only
				static String^ WT_RES_FRAME_CARRIER_SUPPRESSION_11B = gcnew String("carrier.suppression");

				//Psdu Length In Frame. WIFI only
				static String^ WT_RES_FRAME_PSDU_LENGTH = gcnew String("psdu.length");
				//*****************************************************************************
				//                          BT   Frame
				//*****************************************************************************
				//BT BR Freq.Drift,Hz(Payload 10101010)
				static String^ WT_RES_BT_FRAME_CARR_FREQ_DRIFT = gcnew String("BT_CARR_FREQ_DRIFT");

				//BT BR Freq.DriftRate,Hz(Payload 10101010)
				static String^ WT_RES_BT_FRAME_CARR_FREQ_DRIFT_RATE = gcnew String("BT_CARR_FREQ_DRIFT_RATE");

				//BT BR Max Initial freq offset of each burst detected in Hz.
				static String^ WT_RES_BT_FRAME_MAX_CARR_FREQ = gcnew String("BT_MAX_CARR_FREQ");

				//BT BR Delta F1(and WT_ANA_PARM_BT_CARR_FREQ_DRIFT) valid
				static String^ WT_RES_BT_FRAME_DELTA_F1_VALID = gcnew String("BT_DELTA_F1_VALID");

				//BT BR Delta F1 avg,Hz(Payload 00001111)
				static String^ WT_RES_BT_FRAME_DELTA_F1_AVG = gcnew String("BT_DELTA_F1_AVG");

				//BT BR Delta F1 max,Hz
				static String^ WT_RES_BT_FRAME_DELTA_F1_MAX = gcnew String("BT_DELTA_F1_MAX");

				//BT BR Delta F2 valid
				static String^ WT_RES_BT_FRAME_DELTA_F2_VALID = gcnew String("BT_DELTA_F2_VALID");

				//BT BR Delta F2 avg,Hz(Payload 10101010)
				static String^ WT_RES_BT_FRAME_DELTA_F2_AVG = gcnew String("BT_DELTA_F2_AVG");

				//BT BR Delta F2 max,Hz(Payload 10101010)
				static String^ WT_RES_BT_FRAME_DELTA_F2_MAX = gcnew String("BT_DELTA_F2_MAX");

				//BT EDR DEVM Valid
				static String^ WT_RES_BT_FRAME_BT_DEVM_VALID = gcnew String("BT_DEVM_VALID");

				//BT EDR Initial freq error Complex vector, Hz
				static String^ WT_RES_BT_FRAME_CARR_FREQ_BUF = gcnew String("BT_CARR_FREQ_BUF");

				//BT EDR DEVM,%
				static String^ WT_RES_BT_FRAME_BT_DEVM = gcnew String("BT_DEVM");

				//BT EDR DEVM Peak,%
				static String^ WT_RES_BT_FRAME_BT_DEVM_PEAK = gcnew String("BT_DEVM_PEAK");

				//BT EDR Power Diff,dB
				static String^ WT_RES_BT_FRAME_BT_POW_DIFF = gcnew String("BT_POW_DIFF");

				//BT EDR DEVM £¨Less than 20% for 3M, 30% for 2M)
				static String^ WT_RES_BT_FRAME_BT_99PCT = gcnew String("BT_99PCT");

				//BT EDR Omega I,Hz
				static String^ WT_RES_BT_FRAME_EDR_Omega_I = gcnew String("BT_Omega_I");

				//BT EDR Omega O,Hz
				static String^ WT_RES_BT_FRAME_EDR_Omega_O = gcnew String("BT_Omega_O");

				//BT EDR Omega IO,Hz
				static String^ WT_RES_BT_FRAME_EDR_Omega_IO = gcnew String("BT_Omega_IO");

				//BT Bandwidth-20dB Passed Or Failed. 1(1.0) - Passed; 0(0.0) - Failed.
				static String^ WT_RES_BT_FRAME_BW20dB_Passed = gcnew String("BT_BW20dB_Passed");

				//BT Bandwidth-20dB value
				static String^ WT_RES_BT_FRAME_BW20dB = gcnew String("BT_BW20dB_Value");

				//BT BLE Freq Drift Detail Valid
				static String^ WT_RES_BT_FRAME_BLE_DRIFT_DETAIL_VALID = gcnew String("BT_BLE_Drift_Detail_VALID");

				//BT BLE FnMax,Hz
				static String^ WT_RES_BT_FRAME_BLE_FnMax = gcnew String("BT_|Fn| Max");

				//BT BLE F0FnMax,Hz
				static String^ WT_RES_BT_FRAME_BLE_F0FnMax = gcnew String("BT_|F0-Fn| Max");

				//BT BLE Delta_F1F0,Hz
				static String^ WT_RES_BT_FRAME_BLE_Delta_F1F0 = gcnew String("BT_|F1-F0|");

				//BT BLE F0Fn5_Max,Hz
				static String^ WT_RES_BT_FRAME_BLE_FnFn5_Max = gcnew String("BT_|Fn-Fn-5| Max");

				//BT BLE Delta_F0F3,Hz
				static String^ WT_RES_BT_FRAME_BLE_Delta_F0F3 = gcnew String("BT_|F0-F3|");

				//BT BLE Delta_F0Fn3,Hz
				static String^ WT_RES_BT_FRAME_BLE_Delta_F0FN3 = gcnew String("BT_|F0-Fn3|");

				//BT BR/BLE Spectrum Adjacent Channel Power(ACP) dBm,Vector is returned
				static String^ WT_RES_BT_SPETRUM_ADJACENT_CHANNEL_POWER = gcnew String("BT_Spectrum_Acp");

				//BT BR/BLE DetaF2Max Pass Rate£¬%
				static String^ WT_RES_BT_DELTA_F2_PASS_PERCENT = gcnew String("Delta_F2_pass_percent");

				//BT BR/BDR Freq offset header
				static String^ WT_RES_BT_FREQ_OFFSET_HEADER = gcnew String("freq_offset_header");

				//BT BLE Freq offset sync
				static String^ WT_RES_BT_FREQ_OFFSET_SYNC = gcnew String("freq_offset_sync");
				/* Similar to the measurement result for deltaF1Avg as specified in
				BLUETOOTH TEST SPECIFICATION Ver. 1.2/2.0/2.0 + EDR [vol 2] version 2.0.E.2.
				BT BR/EDR Result measured from Header data. Result in Hz.*/
				static String^ WT_RES_BT_RES_FREQ_DEV = gcnew String("freq_deviation");

				//BT BR/EDR Peak to Peak Frequency Deviation, in Hz during header
				static String^ WT_RES_BT_RES_FREQ_DEV_PK_TO_PK = gcnew String("freq_deviationpktopk");

				//BT BR/EDR Delta av access
				static String^ WT_RES_BT_DELTA_F2_AVG_ACCESS = gcnew String("Delta_F2_Av_Access");

				//BT BR/EDR Delta max access
				static String^ WT_RES_BT_DELTA_F2_MAX_ACCESS = gcnew String("Delta_F2_Max_Access");

				//*****************************************************************************
				//                          Zigbee   Frame
				//*****************************************************************************
				//Zigbee EVM(PSDU), dB
				static String^ WT_RES_ZIGBEE_FRAME_EVM_PSDU = gcnew String("Zigbee.evm(psdu)");

				//Zigbee EVM(PSDU), %
				static String^ WT_RES_ZIGBEE_FRAME_EVM_PSDU_PERCENT = gcnew String("Zigbee.evm(psdu).percent");

				//Zigbee EVM(SHR+PHR), dB
				static String^ WT_RES_ZIGBEE_FRAME_EVM_SHRPHR = gcnew String("Zigbee.evm(shr+phr)");

				//Zigbee EVM(SHR+PHR), %
				static String^ WT_RES_ZIGBEE_FRAME_EVM_SHRPHR_PERCENT = gcnew String("Zigbee.evm(shr+phr).percent");

				//Zigbee EVM Offect ,dB
				static String^ WT_RES_ZIGBEE_FRAME_EVM_OFFSET = gcnew String("Zigbee.evm_offset");

				//Zigbee EVM Offect ,%
				static String^ WT_RES_ZIGBEE_FRAME_EVM_OFFSET_PERCENT = gcnew String("Zigbee.evm_offset.percent");
				//*****************************************************************************
				//                          LoRa   Frame
				//*****************************************************************************
				//LoRa Band Edge ,dBc
				static String^ WT_RES_LORA_FRAME_BAND_EDGE = gcnew String("LoRa.Band_Edge");

				//LoRa PSD ,dBm/3KHz
				static String^ WT_RES_LORA_FRAME_PSD = gcnew String("LoRa.Psd");

				//LoRa Bandwidth-20dB value,Hz
				static String^ WT_RES_LORA_FRAME_BW20dB = gcnew String("LoRa_BW20dB_Value");

				//LoRa Bandwidth-6dB value,Hz
				static String^ WT_RES_LORA_FRAME_BW6dB = gcnew String("LoRa_BW6dB_Value");

				//*****************************************************************************
				//                          NBIOT   Frame
				//*****************************************************************************
				//Npusch emission pass or fail, 0: fail, 1: pass
				static String^ WT_RES_NPUSCH_FRAME_EMISSION_PASS = gcnew String("Npusch.emission.pass");

				//Npusch worst emission, dB
				static String^ WT_RES_NPUSCH_FRAME_WORST_EMISSION = gcnew String("Npusch.worst.emission");

				//Npusch aclr pass or fail, 0: fail, 1:pass
				static String^ WT_RES_NPUSCH_FRAME_ACLR_PASS = gcnew String("Npusch.aclr.pass");

				//Npusch aclr value, dBm, [UTRA GSM NB-IOT GSM UTRA]. Vector is returned
				static String^ WT_RES_NPUSCH_FRAME_ACLR = gcnew String("Npusch.aclr");

				//Npusch aclr Relative value, dB, [UTRA GSM GSM UTRA]. Vector is returned
				static String^ WT_RES_NPUSCH_FRAME_RELATIVE_ACLR = gcnew String("Npusch.aclr.relative");

				//*****************************************************************************
				//                          LRWPAN   Frame
				//*****************************************************************************
				//Lrpwan Frequency deviation tolerance(RMS) %
				static String^ WT_RES_LRWPAN_FREQ_DEVIATION_TOLERANCE_RMS = gcnew String("Lrwpan.freq.dev.tolerance.rms");

				//Lrpwan Frequency deviation tolerance(Max) %
				static String^ WT_RES_LRWPAN_FREQ_DEVIATION_TOLERANCE_MAX = gcnew String("Lrwpan.freq.dev.tolerance.max");

				//Lrpwan Frequency deviation tolerance(Min) %
				static String^ WT_RES_LRWPAN_FREQ_DEVIATION_TOLERANCE_MIN = gcnew String("Lrwpan.freq.dev.tolerance.min");

				//Lrpwan Zero crossing tolerance(RMS) %
				static String^ WT_RES_LRWPAN_ZERO_CROSSING_TOLERANCE_RMS = gcnew String("Lrwpan.zero.cross.tolerance.rms");

				//Lrpwan Zero crossing tolerance(Peak) %
				static String^ WT_RES_LRWPAN_ZERO_CROSSING_TOLERANCE_PEAK = gcnew String("Lrwpan.zero.cross.tolerance.peak");

				//Lrpwan Zero crossing tolerance(min) %
				static String^ WT_RES_LRWPAN_ZERO_CROSSING_TOLERANCE_MIN = gcnew String("Lrwpan.zero.cross.tolerance.min");

				//Lrpwan modulation type, 0: 2fsk, 1: 4fsk
				static String^ WT_RES_LRWPAN_MODULATION_TYPE = gcnew String("Lrwpan.modulation.type");

				//*****************************************************************************
				//                          Zwave   Frame
				//*****************************************************************************
				//Zwave init freq offset Hz
				static String^ WT_RES_ZWAVE_INIT_FREQ_OFFSET = gcnew String("Zwave.init.freq.offset");

				//Zwave data rate Kbps
				static String^ WT_RES_ZWAVE_DATA_RATE = gcnew String("Zwave.datarate");

				//Zwave Frequency deviation(RMS) %
				static String^ WT_RES_ZWAVE_FREQ_DEVIATION_RMS = gcnew String("Zwave.freq.dev.rms");

				//Zwave Frequency deviation(MAX) %
				static String^ WT_RES_ZWAVE_FREQ_DEVIATION_MAX = gcnew String("Zwave.freq.dev.max");

				//Zwave Frequency deviation(MIN) %
				static String^ WT_RES_ZWAVE_FREQ_DEVIATION_MIN = gcnew String("Zwave.freq.dev.min");

				//Zwave Zero crossing error(RMS) %
				static String^ WT_RES_ZWAVE_ZERO_CROSSING_ERROR_RMS = gcnew String("Zwave.zero.cross.error.rms");

				//Zwave Zero crossing error(Peak) %
				static String^ WT_RES_ZWAVE_ZERO_CROSSING_ERROR_PEAK = gcnew String("Zwave.zero.cross.error.peak");

				//Zwave symbol clock error ppm
				static String^ WT_RES_ZWAVE_SYMBOL_CLOCK_ERROR = gcnew String("Zwave.symbol.clock.error");

				//Zwave symbol clock jitter ppm
				static String^ WT_RES_ZWAVE_SYMBOL_CLOCK_JITTER = gcnew String("Zwave.symbol.clock.jitter");

				/* demode. Int Value */
				static String^ WT_RES_DEMODE = gcnew String("demode");

				/* Data info */
				static String^ WT_RES_DATA_INFO = gcnew String("data.info");
			};
		}
	}
}
