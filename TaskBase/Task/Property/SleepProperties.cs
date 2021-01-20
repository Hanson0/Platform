using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class SleepProperties : CommonProperties
    {
        private int interval;

        [Category("Common"), Description("sleep time,unit:ms")]
        public int Interval
        {
            get
            {
                return interval;
            }

            set
            {
                this.interval = value;
            }
        }
    }
}
