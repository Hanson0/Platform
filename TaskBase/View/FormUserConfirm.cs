using System;
using System.Threading;
using System.Windows.Forms;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;
using Timer = System.Windows.Forms.Timer;

namespace AILinkFactoryAuto.View
{
    partial class FormUserConfirm : Form
    {
        private DateTime start;
        private TimeSpan countDown;

        private bool result = false;

        private UserConfirmProperties userConfirmProperties;

        private ILog log;

        public bool Result
        {
            get { return result; }
        }

        public FormUserConfirm()
        {
            InitializeComponent();
        }

        public FormUserConfirm(UserConfirmProperties userConfirmProperties, ILog log)
        {
            InitializeComponent();

            this.userConfirmProperties = userConfirmProperties;
            this.log = log;

            lblInfoPass.Text = "PASS：请按" + userConfirmProperties.KeyPass + "键";
            lblInfoFail.Text = "FAIL：请按" + userConfirmProperties.KeyFail + "键";
            txtTips.Text = userConfirmProperties.Tips;
            countDown = new TimeSpan(userConfirmProperties.CountDownTime * 1000 * 10);
        }

        private void FormUserConfirm_Shown(object sender, EventArgs e)
        {
            txtTips.SelectionLength = 0;

            Timer timer = new Timer();
            timer.Enabled = true;
            timer.Interval = 100;
            timer.Tick += Timer_Tick;

            start = DateTime.Now;
            lblCountDown.Text = "倒计时：" + countDown.Seconds + "秒";
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            TimeSpan remainTime = countDown - (DateTime.Now - start);
            if (remainTime.Ticks <= 0)
            {    
                Timer timer = sender as Timer;
                timer.Stop();

                log.Fail("Wait TimeOut, " + countDown.Seconds + "seconds");
                Thread.Sleep(400);

                this.Close();
            }
            else
            {
                lblCountDown.Text = "倒计时：" + remainTime.Seconds + "秒";
            }
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == userConfirmProperties.KeyFail)
            {
                log.Fail("User Press " + userConfirmProperties.KeyFail);
                this.Close();
            }
            else if (keyData == userConfirmProperties.KeyPass)
            {
                result = true;
                log.Pass("User Press " + userConfirmProperties.KeyPass);
                this.Close();
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
    }
}
