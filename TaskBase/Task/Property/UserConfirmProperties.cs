using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AILinkFactoryAuto.Task.Property
{
    public class UserConfirmProperties : CommonProperties
    {
        private int countDownTime = 30000;

        private string tips;

        private Keys keyPass;

        private Keys keyFail;

        public UserConfirmProperties()
        {
            this.RetryCount = 0;
        }

        [Category("Common"), Description("count down time, unit:ms")]
        public int CountDownTime
        {
            get { return countDownTime; }
            set { countDownTime = value; }
        }

        [Category("Common"), Description("tips")]
        public string Tips
        {
            get { return tips; }
            set { tips = value; }
        }

        [Category("Common"), Description("pass key")]
        public Keys KeyPass
        {
            get { return keyPass; }
            set { keyPass = value; }
        }

        [Category("Common"), Description("fail key")]
        public Keys KeyFail
        {
            get { return keyFail; }
            set { keyFail = value; }
        }
    }
}
