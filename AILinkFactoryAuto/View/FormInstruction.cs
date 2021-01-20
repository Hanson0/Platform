using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AILinkFactoryAuto.View
{
    public partial class FormInstruction : Form
    {
        public FormInstruction()
        {
            InitializeComponent();
            Init();
        }

        private void ConfigInstruction_Click(object sender, EventArgs e)
        {
           
            string txtName = Application.StartupPath + @"\Instruction\InitInstruction.txt";
            if (!File.Exists(txtName))
                File.Create(txtName);
            StreamReader sr = new StreamReader(Application.StartupPath + @"\Instruction\InitInstruction.txt");
            string txt = sr.ReadToEnd();
            ShowTxt(txt);

        }

        private void VersionInstruct_Click(object sender, EventArgs e)
        {
            string txtName = Application.StartupPath + @"\Instruction\VersionInstructioin.txt";
            if (!File.Exists(txtName))
                File.Create(txtName);
            StreamReader sr = new StreamReader(Application.StartupPath + @"\Instruction\VersionInstructioin.txt");
            string txt = sr.ReadToEnd();
            ShowTxt( txt);
        }
        private void ShowTxt(string txt)
        {
            if (InvokeRequired)
            {
                this.Invoke(new Action(delegate
                {
                    TxtShow.Text = txt;
                }));
            }
            else
            {
                TxtShow.Text = txt;

            }
        }

        private void Init()
        {
            string Folder = Application.StartupPath + @"\Instruction";
            if (!Directory.Exists(Folder))
                Directory.CreateDirectory(Folder);
            string txtName = Application.StartupPath + @"\Instruction\VersionInstructioin.txt";
            if (!File.Exists(txtName))
                File.Create(txtName);
            StreamReader sr = new StreamReader(Application.StartupPath + @"\Instruction\VersionInstructioin.txt");
            string txt = sr.ReadToEnd();
            ShowTxt(txt);
        }


        private void Platform_Click(object sender, EventArgs e)
        {
            string txtName = Application.StartupPath + @"\Instruction\PlatformInstructioin.txt";
            if (!File.Exists(txtName))
                File.Create(txtName);
            StreamReader sr = new StreamReader(Application.StartupPath + @"\Instruction\PlatformInstructioin.txt");
            string txt = sr.ReadToEnd();
            ShowTxt(txt);
        }
    }
}
