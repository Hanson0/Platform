using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Utils
{
    class CommonUtils
    {
        public static String getCurrentYearMonthDay()
        {
            return DateTime.Now.ToString("yyyyMMdd");
        }
        
        public class FreqGsm
        {
            private double up;

            private double down;

            public double Up
            {
                get { return up; }
                set { up = value; }
            }

            public double Down
            {
                get { return down; }
                set { down = value; }
            }
        }

        //public static FreqGsm ChannelToFreqGsm(CmwGsmBand cmwGsmBand, uint channel)
        //{
        //    FreqGsm freqGsm = new FreqGsm();
        //    uint chan0 = 0;
        //    double freq0 = 0;
        //    double freq1 = 0;
        //    double dlFreq = 0;
        //    double upFreq = 0;
        //    switch (cmwGsmBand)
        //    {
        //        case CmwGsmBand.G085:
        //            freq0 = GsmConstant.GSM_850_DL_START_FREQ;
        //            freq1 = GsmConstant.GSM_850_UL_START_FREQ;
        //            chan0 = GsmConstant.GSM_850_START_CHAN;
        //            break;
        //        case CmwGsmBand.G09:
        //            if(channel >= GsmConstant.PGSM_START_CHAN && channel <= GsmConstant.PGSM_END_CHAN)
        //            {
        //                chan0 = GsmConstant.PGSM_START_CHAN;
        //                freq0 = GsmConstant.PGSM_DL_START_FREQ;
        //                freq1 = GsmConstant.PGSM_UL_START_FREQ;
        //            }
        //            else if(channel >= GsmConstant.EGSM_START_CHAN && channel <= GsmConstant.EGSM_END_CHAN)
        //            {
        //                chan0 = GsmConstant.EGSM_START_CHAN;
        //                freq0 = GsmConstant.EGSM_DL_START_FREQ;
        //                freq1 = GsmConstant.EGSM_UL_START_FREQ;
        //            }
        //            break;
        //        case CmwGsmBand.G18:
        //            freq0 = GsmConstant.DCS_DL_START_FREQ;
        //            freq1 = GsmConstant.DCS_UL_START_FREQ;
        //            chan0 = GsmConstant.DCS_START_CHAN;
        //            break;
        //        case CmwGsmBand.G19:
        //            freq0 = GsmConstant.PCS_DL_START_FREQ;
        //            freq1 = GsmConstant.PCS_UL_START_FREQ;
        //            chan0 = GsmConstant.PCS_START_CHAN;
        //            break;
        //        default:
        //            break;
        //    }
        //    dlFreq = freq0 + 0.2 * (channel - chan0);
        //    upFreq = freq1 + 0.2 * (channel - chan0);
        //    freqGsm.Down = dlFreq;
        //    freqGsm.Up = upFreq;
        //    return freqGsm;
        //}       
    }
}
