using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Task;

namespace AILinkFactoryAuto.Utils
{
    public class WifiUtils
    {
        public static int Freq2Channel(double freqMhz)
        {
            int channel = 0;

            if (!((freqMhz >= 2412.0 && freqMhz <= 2472.0) || (freqMhz >= 5180.0 && freqMhz <= 5885.0)))
            {
                throw new BaseException(string.Format("freqMhz {0} is invalid", freqMhz));
            }

            if (freqMhz >= 2412.0 && freqMhz <= 2472.0)
            {
                double temp = (freqMhz - 2412.0) % 5.0;
                if (temp != 0)
                {
                    throw new BaseException(string.Format("freqMhz {0} is invalid", freqMhz));
                }
                channel = (int)((freqMhz - 2412.0) / 5.0 + 1.0);
            }


            if (freqMhz >= 5180.0 && freqMhz <= 5885.0)
            {
                if (freqMhz >= 5180.0 && freqMhz <= 5320.0)
                {
                    double temp = (freqMhz - 5180.0) % 5.0;
                    if (temp != 0)
                    {
                        throw new BaseException(string.Format("freqMhz {0} is invalid", freqMhz));
                    }
                    channel = (int)((freqMhz - 5180.0) / 5.0 + 36.0);
                }

                if (freqMhz >= 5500.0 && freqMhz <= 5885.0)
                {
                    double temp = (freqMhz - 5500.0) % 5.0;
                    if (temp != 0)
                    {
                        throw new BaseException(string.Format("freqMhz {0} is invalid", freqMhz));
                    }
                    channel = (int)((freqMhz - 5500.0) / 5.0 + 100.0);
                }
            }

            if (channel == 0)
            {
                throw new BaseException(string.Format("freqMhz {0} is invalid", freqMhz));
            }

            return channel;
        }
    }
}
