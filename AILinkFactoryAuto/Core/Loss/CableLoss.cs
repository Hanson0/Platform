using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Instrument.Property;

namespace AILinkFactoryAuto.Core.Loss
{
    class CableLoss
    {
        private List<CableLossItem> cableLossList = new List<CableLossItem>();

        public void Add(CableLossItem cableLossItem)
        {
            cableLossList.Add(cableLossItem);
        }

        public double GetLoss(double freq, CmwPort cmwPort)
        {
            double loss = 0;

            foreach (var cableLossItem in cableLossList)
            {
                if (freq >= cableLossItem.FreqStart && 
                    freq <= cableLossItem.FreqEnd && 
                    cmwPort == cableLossItem.CmwPort)
                {
                    loss = cableLossItem.Loss;
                    break;
                }
            }

            return loss;
        }
    }
}
