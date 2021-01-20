using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AILinkFactoryAuto.Properties;

namespace AILinkFactoryAuto.View
{
    public partial class FormAbout : Form
    {
        public FormAbout()
        {
            InitializeComponent();
        }

        private void FormAbout_Load(object sender, EventArgs e)
        {
            this.Shown += FormAbout_Shown;
            this.picLogo.Image = Resources.logo;
        }

        private void FormAbout_Shown(object sender, EventArgs e)
        {
            textBox1.SelectionStart = textBox1.TextLength;
            textBox1.SelectionLength = 0;
        }
    }
}
