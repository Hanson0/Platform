using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public enum LogType
    {
        MAC,
        IMEI,
        SN
    }

    public class InitProperties : CommonProperties
    {
        private bool topMost;

        [Category("Common"), Description("top most")]
        public bool TopMost
        {
            get { return topMost; }
            set { topMost = value; }
        }
    }
}
