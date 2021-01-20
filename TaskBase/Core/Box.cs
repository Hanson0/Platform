using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AILinkFactoryAuto.Core
{
    public class Box
    {
        private static readonly string CAPTION = "爱联世界";

        public static DialogResult ShowWarnOkCancel(string info, string caption)
        {
            return MessageBox.Show(info, caption, MessageBoxButtons.OKCancel, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2);
        }

        public static DialogResult ShowInfoOk(string info, string caption)
        {
            return MessageBox.Show(info, caption, MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        public static DialogResult ShowErrorOk(string info, string caption)
        {
            return MessageBox.Show(info, caption, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        public static DialogResult ShowInfoOk(string info)
        {
            return ShowInfoOk(info, CAPTION);
        }

        public static DialogResult ShowErrorOk(string info)
        {
            return ShowErrorOk(info, CAPTION);
        }

        public static DialogResult ShowWarnOkCancel(string info)
        {
            return ShowWarnOkCancel(info, CAPTION);
        }
    }
}
