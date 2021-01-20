using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;

namespace AILinkFactoryAuto.Core
{
    class StopWatch
    {
        private TimeSpan span;
        private DateTime startTime;
        private Timer timer = new Timer();

        public delegate void UpdateUi(string time);
        public UpdateUi UpdateUiCallBack;

        private bool isRun;

        public string TestTime
        {
            get
            {
                return double.Parse(span.TotalSeconds.ToString("#.000")).ToString();
            }
        }

        public void Start()
        {
            startTime = DateTime.Now;
            timer.Enabled = true;
            timer.Interval = 50;
            timer.AutoReset = true;
            timer.Elapsed += Timer_Elapsed;
            isRun = true;
            timer.Start();
        }

        private void Timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            if (isRun)
            {
                span = DateTime.Now - startTime;
                DateTime spanDateTime = new DateTime(span.Ticks);
                UpdateUiCallBack(spanDateTime.ToString("HH:mm:ss.fff"));
            }
        }

        public void Stop()
        {
            isRun = false;
            timer.Stop();
        }
    }
}
