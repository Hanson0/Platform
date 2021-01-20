using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class ScanCodeProperties : CommonProperties
    {
        public ScanCodeProperties()
        {
            this.RetryCount = 0;
            this.Timeout = 60 * 1000;
        }

        private string dutName;

        private uint order;

        [Category("Common"), Description("dut's name")]
        public string DutName
        {
            get { return dutName; }
            set { dutName = value; }
        }

        [Category("Common"), Description("the order of shown")]
        public uint Order
        {
            get { return order; }
            set { order = value; }
        }
    }
}
