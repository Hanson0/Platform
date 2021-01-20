using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class ReadMacNetCardProperties : CommonProperties
    {
        private string netCardName;

        [Category("Common"), Description("net card name")]
        public string NetCardName
        {
            get
            {
                return netCardName;
            }

            set
            {
                netCardName = value;
            }
        }
    }
}
