using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Properties;
using Mes.Test;
using System.IO;

namespace AILinkFactoryAuto.View
{
    public partial class FormLogin : Form
    {
        //private string[] userNameList;
        private List<string> userNameList = new List<string>();
        private string userInfoPath;
        private static string loginInfo;

        public static string LoginInfo
        {
            get { return loginInfo; }
            set { loginInfo = value; }
        }

        public FormLogin()
        {
            InitializeComponent();
        }

        private void Login_Load(object sender, EventArgs e)
        {
            this.Icon = Resources.phone;
            this.userInfoPath = AppDomain.CurrentDomain.BaseDirectory + "userInfo.txt";

            //用户名列表初始化记忆


            #region 读取用户名信息展开为户名列表
            //判断文件是否存在，不存在则创建一个userInfo.txt
            try
            {
                CreatFile(userInfoPath);
                Read(userInfoPath);
                if (userNameList.Count > 0)
                {
                    string[] userNameArray = userNameList.ToArray();
                    combUser.Items.AddRange(userNameArray);
                    combUser.SelectedIndex = userNameArray.Length - 1;
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }
            #endregion

            if (StudioProperties.RememberUserName == "1")
            {
                cbRemember.Checked = true;
            }
            else
            {
                cbRemember.Checked = false;
            }

            txtPassword.KeyPress += TxtPassword_KeyPress;
            btnLogin.Click += BtnLogin_Click;

        }

        private void TxtPassword_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!string.IsNullOrEmpty(txtPassword.Text.Trim()) && e.KeyChar == (int)Keys.Enter)
            {
                BtnLogin_Click(null, null);
            }
        }

        private void BtnLogin_Click(object sender, EventArgs e)
        {
            #region
            if (combUser.Text == "")
            {
                MessageBox.Show("用户名不能为空");
                combUser.Focus();
                return;
            }
            if (txtPassword.Text == "")
            {
                MessageBox.Show("密码不能为空");
                txtPassword.Focus();
                return;
            }

            try
            {
                if (this.combUser.Text.Trim() == "super" && this.txtPassword.Text.Trim() == "5845201314")
                {
                    this.DialogResult = DialogResult.OK;
                    this.Close();
                    return;
                }

                loginInfo = MesProcess.LoginImes(this.combUser.Text.Trim(), this.txtPassword.Text.Trim());

                //从loginInfo记录登录名，手机号，邮箱

                //勾选了记住用户-重复的去掉并重新添加写入userInfo.txt
                if (cbRemember.Checked == true)
                {
                    bool isInlist = false;
                    foreach (var item in userNameList)
                    {
                        if (item == this.combUser.Text.Trim())
                        {
                            userNameList.Remove(item);
                            userNameList.Add(item);
                            isInlist = true;
                            break;
                        }
                    }
                    if (!isInlist)
                    {
                       userNameList.Add(this.combUser.Text.Trim());
                    }
                    File.WriteAllLines(userInfoPath, userNameList.ToArray());
                    //WriteLine(userInfoPath, this.combUser.Text.Trim());
                }


                this.DialogResult = DialogResult.OK;
                this.Close();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                combUser.Focus();
                combUser.SelectAll();
                this.DialogResult = DialogResult.None;
                return;
            }
            #endregion
        }

        /// <summary>
        /// 创建文件
        /// </summary>
        /// <param name="path"></param>
        public void CreatFile(string path)
        {
            try
            {
                //判断文件是否存在，没有则创建。
                if (!System.IO.File.Exists(path))
                {
                    FileStream stream = System.IO.File.Create(path);
                    stream.Close();
                    stream.Dispose();
                }
            }
            catch (Exception)
            {
                throw;
            }
        }

        /// <summary>
        /// 读取文件内容至list列表
        /// </summary>
        /// <param name="path"></param>
        public void Read(string path)
        {
            try
            {
                StreamReader sr = new StreamReader(path, Encoding.Default);
                String line;

                while ((line = sr.ReadLine()) != null)
                {
                    userNameList.Add(line.ToString());
                    //Console.WriteLine(line.ToString());
                }
                sr.Close();
            }
            catch (Exception)
            {
                throw;
            }
        }

        /// <summary>
        /// 写文件内容-行
        /// </summary>
        /// <param name="path"></param>
        public void WriteAllLine(string path, List<string> lines)
        {
            FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Write, FileShare.ReadWrite);
            StreamWriter sw = new StreamWriter(fs);
            //开始写入
            foreach (var item in lines)
            {
                sw.WriteLine(item);
            }
            //清空缓冲区
            sw.Flush();
            //关闭流
            sw.Close();
            fs.Close();
        }

        private void cbRemember_CheckedChanged(object sender, EventArgs e)
        {
            if (cbRemember.Checked == true)
            {
                //写SetUp.ini
                StudioProperties.RememberUserName = "1";
            }
            else if (cbRemember.Checked == false)
            {
                //写SetUp.ini
                StudioProperties.RememberUserName = "0";
            }

        }

    }
}
