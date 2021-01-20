using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class CheckMacConsistencyProperties : CommonProperties
    {
        private string deviceMac;
        [Category("Common"), Description("Check DeviceMac,example:{Dev_WifiMac}")]
        public string DeviceMac
        {
            get { return deviceMac; }
            set { deviceMac = value; }
        }

    }
}
