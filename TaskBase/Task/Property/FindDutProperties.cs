using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class FindDutProperties : CommonProperties
    {
        private string dutKeywords;

        [Category("Common"), Description("dut keywords")]
        public string DutKeywords
        {
            get { return dutKeywords; }
            set { dutKeywords = value; }
        }
    }
}
