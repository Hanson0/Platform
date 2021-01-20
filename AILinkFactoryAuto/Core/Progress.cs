using AILinkFactoryAuto.View.UserContol;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AILinkFactoryAuto.Core
{
    //进度条和lable数值显示
    class Progress
    {
        private ColorProgressBar progressBar;

        private Label label;

        public Progress(ColorProgressBar progressBar, Label label)
        {
            this.progressBar = progressBar;
            this.label = label;
            this.SetBrush(Brushes.Gray);
        }

        public void SetProgressMinMax(int minimum,int maximum)
        {
            if (this.progressBar.InvokeRequired)
            {
                this.progressBar.Invoke((EventHandler) delegate
                {
                    this.progressBar.Minimum = minimum;
                    this.progressBar.Maximum = maximum;
                });
            }
            else
            {
                this.progressBar.Minimum = minimum;
                this.progressBar.Maximum = maximum;
            }
        }

        public void SetProgress(int value)
        {
            if (this.progressBar.InvokeRequired)
            {
                this.progressBar.Invoke((EventHandler)delegate
                {
                    this.progressBar.Value = value;
                    this.label.Text = value + "/" + this.progressBar.Maximum;
                });
            }
            else
            {
                this.progressBar.Value = value;
                this.label.Text = value + "/" + this.progressBar.Maximum;
            }
        }

        public void SetBrush(Brush brush)
        {
            if (this.progressBar.InvokeRequired)
            {
                this.progressBar.Invoke((EventHandler)delegate
                {
                    this.progressBar.SetBrush(brush);
                });
            }
            else
            {
                this.progressBar.SetBrush(brush);
            }

        }
    }
}
