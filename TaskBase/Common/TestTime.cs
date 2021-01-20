using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Common
{
    public class TestTime
    {
        private DateTime now;

        public void StartRecord()
        {
            this.now = DateTime.Now;
        }

        public string StopRecord()
        {
            TimeSpan timeSpan = DateTime.Now - this.now;
            string timeConsuming = timeSpan.ToString("g");
            return timeConsuming;
        }
    }
}
