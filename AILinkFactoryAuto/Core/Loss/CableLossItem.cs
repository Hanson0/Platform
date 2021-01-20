using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Instrument.Property;

namespace AILinkFactoryAuto.Core.Loss
{
    class CableLossItem
    {

        private CmwPort cmwPort;

        private double freqStart;

        private double freqEnd;

        private double loss;

        public CmwPort CmwPort
        {
            get { return cmwPort; }
            set { cmwPort = value; }
        }

        public double FreqStart
        {
            get { return freqStart; }
            set { freqStart = value; }
        }

        public double FreqEnd
        {
            get { return freqEnd; }
            set { freqEnd = value; }
        }

        public double Loss
        {
            get { return loss; }
            set { loss = value; }
        }
    }
}
