using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class SyncProperties : CommonProperties
    {
        public SyncProperties()
        {
            this.RetryCount = 0;
            this.ExecuteCondition = ExecuteCondition.ALWAYS;
        }

        private string key;

        [Category("Common"), Description("sync key")]
        public string Key
        {
            get { return key; }
            set { key = value; }
        }
    }
}
