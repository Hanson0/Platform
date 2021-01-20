using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AILinkFactoryAuto.View
{
    public partial class FormScanCode : Form
    {
        private string dutName;

        public string DutName
        {
            get { return dutName; }
            set { dutName = value; }
        }

        private string labelSn;

        public string LabelSn
        {
            get { return labelSn; }
            set { labelSn = value; }
        }

        public FormScanCode()
        {
            InitializeComponent();
        }

        private void FormScanCode_Load(object sender, EventArgs e)
        {
            this.txtBarcode.KeyPress += TxtBarcode_KeyPress;
            this.Shown += FormScanCode_Shown;
        }

        private void FormScanCode_Shown(object sender, EventArgs e)
        {
            this.lblDutName.Text = this.dutName;
        }

        private void TxtBarcode_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (int) Keys.Enter)
            {
                this.labelSn = this.txtBarcode.Text;
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
        }
    }
}
