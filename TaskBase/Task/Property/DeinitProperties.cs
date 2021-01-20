using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class DeinitProperties : CommonProperties
    {
        private bool topMost;

        private LogType logType;

        [Category("Common"), Description("前端显示")]
        public bool TopMost
        {
            get { return topMost; }
            set { topMost = value; }
        }

        [Category("Common"), Description("对接iMES，log的类型")]
        public LogType LogType
        {
            get { return logType; }
            set { logType = value; }
        }
    }
}
