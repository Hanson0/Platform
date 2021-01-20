using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Utils;
using log4net;
using log4net.Repository.Hierarchy;
using WeifenLuo.WinFormsUI.Docking;

namespace AILinkFactoryAuto.View
{
    public partial class FormInfo : DockContent
    {
        public FormInfo()
        {
            InitializeComponent();
        }

        private void Info(string info)
        {
            this.Invoke((EventHandler) delegate
            {
                this.rtcInfo.AppendText(info);
                this.rtcInfo.SelectionStart = this.rtcInfo.TextLength;
                this.rtcInfo.SelectionLength = 0;
                this.rtcInfo.ScrollToCaret();
            });
        }

        private void FormInfo_Load(object sender, EventArgs e)
        {
            this.Text = "Information";
            this.Closing += FormInfo_Closing;
            this.rtcInfo.ReadOnly = true;

            InitLogInfo();
        }

        private void InitLogInfo()
        {
            UiLogAppender uiLogAppender = LogUtils.GetAppender<UiLogAppender>();
            uiLogAppender.UiLogReceived += UiLogAppender_UiLogReceived;
        }

        private void UiLogAppender_UiLogReceived(object sender, UiLogEventArgs e)
        {
            Info(e.Message);
        }

        private void FormInfo_Closing(object sender, CancelEventArgs e)
        {
            this.PanelPane.DockState = DockState.DockBottomAutoHide;
            e.Cancel = true;
        }
    }
}
