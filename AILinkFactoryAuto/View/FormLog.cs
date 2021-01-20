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
using WeifenLuo.WinFormsUI.Docking;

namespace AILinkFactoryAuto.View
{
    public partial class FormLog : DockContent
    {
        public FormLog()
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
            this.Closing += FormInfo_Closing;
            this.rtcInfo.ReadOnly = true;
            this.Shown += FormLog_Shown;
            UiLogDebugAppender uiLogDebugAppender = LogUtils.GetAppender<UiLogDebugAppender>();
            uiLogDebugAppender.UiLogReceived += UiLogDebugAppender_UiLogReceived;
        }

        private void FormLog_Shown(object sender, EventArgs e)
        {
            LogUtils.UiInfo.Info("FormLog................Success!");
        }

        private void UiLogDebugAppender_UiLogReceived(object sender, UiLogEventArgs e)
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
