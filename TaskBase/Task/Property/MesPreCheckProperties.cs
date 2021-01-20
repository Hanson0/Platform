using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class MesPreCheckProperties : CommonProperties
    {
        private bool enableCheckSn;

        private bool enableCheckMac;

        private bool enableCheckImei;

        [Category("Common"), Description("iMES系统，是否打开SN预检查")]
        public bool EnableCheckSn
        {
            get { return enableCheckSn; }
            set { enableCheckSn = value; }
        }

        [Category("Common"), Description("iMES系统，是否打开MAC预检查")]
        public bool EnableCheckMac
        {
            get { return enableCheckMac; }
            set { enableCheckMac = value; }
        }

        [Category("Common"), Description("iMES系统，是否打开IMEI预检查")]
        public bool EnableCheckImei
        {
            get { return enableCheckImei; }
            set { enableCheckImei = value; }
        }
    }
}
