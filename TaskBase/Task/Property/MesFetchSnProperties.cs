using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class MesFetchSnProperties : CommonProperties
    {
        private bool isNeedInc1;

        [Category("Common"), Description("is need +1 from mac")]
        public bool IsNeedInc1
        {
            get { return isNeedInc1; }
            set { isNeedInc1 = value; }
        }
    }
}
