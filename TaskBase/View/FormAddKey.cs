using System;
using System.Windows.Forms;
using AILinkFactoryAuto.Core;

namespace AILinkFactoryAuto.View
{
    public partial class FormAddKey : Form
    {
        private string key;

        public string Key
        {
            get { return key; }
        }

        public FormAddKey()
        {
            InitializeComponent();
        }

        private void FormAddKey_Load(object sender, EventArgs e)
        {
            this.btnConfirm.Click += BtnConfirm_Click;
            this.btnCancel.Click += BtnCancel_Click;
        }

        private void BtnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void BtnConfirm_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(txtKey.Text))
            {
                Box.ShowInfoOk("txtKey is null");
                return;
            }

            this.key = txtKey.Text;
            Close();
        }
    }
}
