using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AILinkFactoryAuto.Utils;

namespace AILinkFactoryAuto.Core
{
    class Log : ILog
    {
        private RichTextBox rtxLog;

        private string logFileMessage;

        public string LogFileMessage
        {
            get
            {
                return logFileMessage;
            }
        }

        public Log(RichTextBox rtxLog)
        {
            this.rtxLog = rtxLog;
        }

        public void Info(string log)
        {
            LogUtils.UiDebug.Info(log);
            Display(log, Color.Black);
        }

        public void Fail(string log)
        {
            LogUtils.UiDebug.Error(log);
            Display(log, Color.Red);
        }
        public void Warn(string log)
        {
            LogUtils.UiDebug.Warn(log);
            Display(log, Color.Orange);
        }

        public void Pass(string log)
        {
            LogUtils.UiDebug.Info(log);
            Display(log, Color.Green);
        }

        private void Display(string log, Color color)
        {
            log = log + Environment.NewLine;
            logFileMessage += log;
            rtxLog.Invoke((EventHandler)delegate
            {
                if (!string.IsNullOrEmpty(log))
                {
                    int start = rtxLog.TextLength;
                    rtxLog.AppendText(log);
                    rtxLog.SelectionStart = start;
                    rtxLog.SelectionLength = log.Length;
                    rtxLog.SelectionColor = color;

                    rtxLog.SelectionStart = rtxLog.TextLength;
                    rtxLog.SelectionLength = 0;
                }
                else
                {
                    rtxLog.AppendText(log);
                }
                rtxLog.AppendText("");
                rtxLog.ScrollToCaret();
                //rtxLog.Focus();

                ILogFile totalLogFile = new LogFile("./log_total/" + CommonUtils.getCurrentYearMonthDay() + ".log");
                totalLogFile.AppendLine(log);
            });
        }
    }
}
