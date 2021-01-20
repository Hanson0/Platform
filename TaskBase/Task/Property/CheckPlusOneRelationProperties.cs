using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class CheckPlusOneRelationProperties : CommonProperties
    {
        private string devWifiMac;
        private string devBtMac;
        [Category("Common"), Description("Compare object")]
        public string DevWifiMac
        {
            get { return devWifiMac; }
            set { devWifiMac = value; }
        }


        [Category("Common"), Description("Compare object")]
        public string DevBtMac
        {
            get { return devBtMac; }
            set { devBtMac = value; }
        }

    }
}
