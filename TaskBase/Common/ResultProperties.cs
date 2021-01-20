using System;
using System.IO;
using System.Text;
using System.Windows.Forms;
using AILinkFactoryAuto.Core;

namespace AILinkFactoryAuto.Common
{
    public class ResultProperties
    {
        private static string defaultFileName = "SetUp.ini";
        private static string defaultFullFileName;
        private static int defaultCapacityOfStringbuilder = 256;

        private int pass;
        private int fail;

        private ToolStripLabel lblPass;

        private ToolStripLabel lblFail;

        private ToolStripLabel lblTotal;

        private ToolStripLabel lblYeild;

        private Form form;

        public int Pass => pass;

        public int Fail => fail;

        public ToolStripLabel LblPass
        {
            set { lblPass = value; }
        }

        public ToolStripLabel LblFail
        {
            set { lblFail = value; }
        }

        public ToolStripLabel LblTotal
        {
            set { lblTotal = value; }
        }

        public ToolStripLabel LblYeild
        {
            set { lblYeild = value; }
        }

        public Form Form
        {
            set { form = value; }
        }

        public ResultProperties()
        {
            defaultFullFileName = Path.Combine(Environment.CurrentDirectory, defaultFileName);
        }

        public void InitResult()
        {
            try
            {
                StringBuilder stringBuilder = new StringBuilder(defaultCapacityOfStringbuilder);
                Ini.GetPrivateProfileString("Result", "Pass", "", stringBuilder, 256, defaultFullFileName);
                pass = int.Parse(stringBuilder.ToString());

                Ini.GetPrivateProfileString("Result", "Fail", "", stringBuilder, 256, defaultFullFileName);
                fail = int.Parse(stringBuilder.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }

            CalculateResult();
        }

        private void CalculateResult()
        {
            this.form.Invoke((EventHandler)delegate
            {
                lblPass.Text = pass.ToString();
                lblFail.Text = fail.ToString();
                int total = pass + fail;
                lblTotal.Text = total.ToString();

                double yield = 0;
                if (total != 0)
                {
                    yield = pass / (total * 1.0);
                }

                lblYeild.Text = string.Format("{0:0.00%}", yield);
            });

            SaveResult();
        }

        public void IncPass()
        {
            pass = pass + 1;
            CalculateResult();
        }

        public void IncFail()
        {
            fail = fail + 1;
            CalculateResult();
        }

        public void ClearResult()
        {
            pass = 0;
            fail = 0;
            CalculateResult();
        }

        private void SaveResult()
        {
            Ini.WritePrivateProfileString("Result", "Pass", pass.ToString(), defaultFullFileName);
            Ini.WritePrivateProfileString("Result", "Fail", fail.ToString(), defaultFullFileName);
        }
    }
}
