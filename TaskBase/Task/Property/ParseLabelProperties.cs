using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class ParseLabelProperties : CommonProperties
    {
        private int snLocation;

        private int imeiLocation;

        private int meidLocation;

        private int macLocation;

        public ParseLabelProperties()
        {
            this.RetryCount = 0;
        }

        [Category("Common"), Description("sn's location")]
        public int SnLocation
        {
            get { return snLocation; }
            set { snLocation = value; }
        }

        [Category("Common"), Description("imei's location")]
        public int ImeiLocation
        {
            get { return imeiLocation; }
            set { imeiLocation = value; }
        }

        [Category("Common"), Description("meid's location")]
        public int MeidLocation
        {
            get { return meidLocation; }
            set { meidLocation = value; }
        }

        [Category("Common"), Description("mac's location")]
        public int MacLocation
        {
            get { return macLocation; }
            set { macLocation = value; }
        }
    }
}
