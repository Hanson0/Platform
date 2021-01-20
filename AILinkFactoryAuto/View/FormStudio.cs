using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using AILinkFactoryAuto.Common;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Peripherals;
using AILinkFactoryAuto.Properties;
using AILinkFactoryAuto.Utils;
using WeifenLuo.WinFormsUI.Docking;

namespace AILinkFactoryAuto.View
{
    public partial class FormStudio : Form
    {
        [DllImport("user32.dll", EntryPoint = "SendMessage")]
        private static extern int SendMessage(IntPtr hwnd, int wMsg, int wParam, int lParam);

        [DllImport("user32.dll", EntryPoint = "PostMessage")]
        private static extern int PostMessage(IntPtr hwnd, int wMsg, int wParam, int lParam);

        private const int WM_USER_AUTOSTART = 0x0400 + 1;

        private string filenameLayout = "./projects/layout.xml";

        private string projectsPath;

        private StopWatch stopWatch = new StopWatch();

        private ResultProperties resultProperties = new ResultProperties();

        public FormStudio()
        {
            InitializeComponent();
        }

        private void FormStudio_Load(object sender, EventArgs e)
        {
            Thread.CurrentThread.Name = "FormStudio";
            this.Icon = Resources.logo1;
            this.toolStripLabel7.Text = "FPY";

            ToolStripMenuItem tsmVerify =new ToolStripMenuItem();
            tsmVerify.Name = "tsmVerify";
            tsmVerify.Size = new System.Drawing.Size(124, 22);
            tsmVerify.Text = "线损校准工具";

            this.工具TToolStripMenuItem.DropDownItems.Insert(0, tsmVerify);
            //this.工具TToolStripMenuItem.DropDownItems.Add(tsmVerify);
            //this.工具TToolStripMenuItem.DropDownItems.AddRange(tsmVerify)

            this.Shown += FormStudio_Shown;
            this.Closing += FormStudio_Closing;

            DockPanelUtils.SetDockPanel(this.dockPanel);
            this.statusStrip.LayoutStyle = ToolStripLayoutStyle.StackWithOverflow;

            this.tsslTime.Alignment = ToolStripItemAlignment.Right;

            this.Instruction.Visible = false;

            //toolStrip1设置
            toolStrip1.AutoSize = false;
            toolStrip1.ImageScalingSize = new System.Drawing.Size(110, 125);
            toolStrip1.Size = new System.Drawing.Size(1008, 125);

            tsbStart.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            tsbStart.Size = new System.Drawing.Size(132, 125);

            tsbStop.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            tsbStop.Size = new System.Drawing.Size(132, 125);
            tsbAutoStart.Visible = false;

            this.tsmExit.Click += TsmExit_Click;
            this.tsmAbout.Click += TsmAbout_Click;
            tsmVerify.Click += TsmVerify_Click;
            
            this.tsmCalc.Click += TsmCalc_Click;
            this.tsmNote.Click += TsmNote_Click;
            this.tsmPaint.Click += TsmPaint_Click;
            this.tsmSaveLayout.Click += TsmSaveLayout_Click;
            this.tsmDeleteLayout.Click += TsmDeleteLayout_Click;
            this.tsbStart.Click += TsbStart_Click;
            this.tsbStop.Click += TsbStop_Click;
            this.tsbAutoStart.Click += TsbAutoStart_Click;
            this.tsmGenJts.Click += TsmGenJts_Click;

            this.tsbSetup.Visible = false;

            this.stopWatch.UpdateUiCallBack = DisplayStopWatch;

            this.resultProperties.Form = this;
            this.resultProperties.LblPass = toolStripLabel2;
            this.resultProperties.LblFail = toolStripLabel4;
            this.resultProperties.LblTotal = toolStripLabel6;
            this.resultProperties.LblYeild = toolStripLabel8;
            this.resultProperties.InitResult();

            this.toolStripLabel1.Click += ClearResult;
            this.toolStripLabel2.Click += ClearResult;
            this.toolStripLabel3.Click += ClearResult;
            this.toolStripLabel4.Click += ClearResult;
            this.toolStripLabel5.Click += ClearResult;
            this.toolStripLabel6.Click += ClearResult;
            this.toolStripLabel7.Click += ClearResult;
            this.toolStripLabel8.Click += ClearResult;

            InitTime();
            InitProjectInfo();
            InitPluginsPath();
            ProcessAutoStart();
        }

        private void ProcessAutoStart()
        {
            bool autoStart = StudioProperties.AutoStart;
            if (autoStart)
            {
                this.tsbAutoStart.Text = "自动";
                this.tsbAutoStart.Image = Resources.auto;
            }
            else
            {
                this.tsbAutoStart.Text = "手动";
                this.tsbAutoStart.Image = Resources.manual;
            }
        }

        private void TsbAutoStart_Click(object sender, EventArgs e)
        {
            StudioProperties.AutoStart = !StudioProperties.AutoStart;
            ProcessAutoStart();
        }

        private void InitPluginsPath()
        {
            string path = "./plugins";
            if (!Directory.Exists(path))
            {
                Directory.CreateDirectory(path);
            }
        }

        private void TsmGenJts_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(this.tscbProject.ComboBox.Text))
            {
                Box.ShowErrorOk("请在下面的路劲创建工程目录\r\n" + this.projectsPath);
                return;
            }

            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Multiselect = false;
            openFileDialog.InitialDirectory = Environment.CurrentDirectory;
            openFileDialog.Title = "生成测试序列";
            openFileDialog.Filter = "测试序列(AILinkFactoryAuto.GenJts.*.dll)|AILinkFactoryAuto.GenJts.*.dll";
            DialogResult dialogResult = openFileDialog.ShowDialog();
            if (dialogResult == DialogResult.OK)
            {
                Assembly assembly = Assembly.LoadFrom(openFileDialog.FileName);
                Type[] types = assembly.GetTypes();
                foreach (Type type in types)
                {
                    if (typeof(IGenJts).IsAssignableFrom(type))
                    {
                        IGenJts genJts = Activator.CreateInstance(type) as IGenJts;
                        genJts.ProjectPath = Path.Combine(this.projectsPath, this.tscbProject.ComboBox.Text);
                        genJts.StartPosition = FormStartPosition.CenterParent;
                        genJts.ShowDialog();
                    }
                }
            }
        }

        private void FormStudio_Closing(object sender, CancelEventArgs e)
        {
            bool isRunning = false;
            foreach (var content in this.dockPanel.Contents)
            {
                IRunnable runnable = content as IRunnable;
                if (runnable != null)
                {
                    if (runnable.IsRunning)
                    {
                        isRunning = true;
                        break;
                    }
                }
            }

            if (isRunning)
            {
                e.Cancel = true;
            }
        }

        private void ClearResult(object sender, EventArgs e)
        {
            DialogResult dialogResult = MessageBox.Show("即将清零，请确认！", "提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Asterisk, MessageBoxDefaultButton.Button2);
            if (dialogResult == DialogResult.OK)
            {
                resultProperties.ClearResult();
                MessageBox.Show("清零成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void TsmDeleteLayout_Click(object sender, EventArgs e)
        {
            if (File.Exists(this.filenameLayout))
            {
                FileInfo fileInfo = new FileInfo(this.filenameLayout);
                fileInfo.Delete();
                LogUtils.UiInfo.Info(string.Format("delete layout {0} success", filenameLayout));
                Box.ShowInfoOk(string.Format("delete layout {0} success", filenameLayout));
            }
            else
            {
                LogUtils.UiInfo.Error(string.Format("delete layout {0} fail", filenameLayout));
                Box.ShowErrorOk(string.Format("delete layout {0} fail", filenameLayout));
            }
            this.tscbProject.ComboBox.Enabled = true;
        }

        private void TsbStart_Click(object sender, EventArgs e)
        {
            try
            {
                Start();
            }
            catch (Exception exception)
            {
                Box.ShowErrorOk(exception.Message);
            }
        }

        private void Start()
        {
            lock (this)
            {
                bool isRunning = false;
                List<IRunnable> runnableList = new List<IRunnable>();
                foreach (var content in this.dockPanel.Contents)
                {
                    IRunnable runnable = content as IRunnable;
                    if (runnable != null)
                    {
                        runnableList.Add(runnable);
                        if (runnable.IsRunning)
                        {
                            isRunning = true;
                            break;
                        }
                    }
                }

                if (isRunning)
                {
                    throw new Exception("工作线程正在运行......");
                }

                List<Thread> threadList = new List<Thread>();
                foreach (var runnable in runnableList)
                {
                    Thread thread = new Thread(runnable.Run);
                    thread.Name = "Thread-" + runnable.ThreadName;
                    threadList.Add(thread);
                    runnable.Start();
                }

                this.tsbStart.Enabled = false;

                CountLatch sync = new CountLatch((uint)runnableList.Count);
                foreach (var runnable in runnableList)
                {
                    runnable.Sync = sync;
                }

                foreach (var thread in threadList)
                {
                    thread.Start();
                }
            }          
        }

        private void TsbStop_Click(object sender, EventArgs e)
        {
            foreach (var content in this.dockPanel.Contents)
            {
                IRunnable runnable = content as IRunnable;
                if (runnable != null)
                {
                    runnable.Stop();
                }
            }

            StudioProperties.AutoStart = false;
            ProcessAutoStart();
            this.tsbStart.Enabled = true;
        }

        private void DisplayStopWatch(string time)
        {
            try
            {
                this.Invoke((EventHandler)delegate
                {
                    this.tslStopWatch.Text = time;
                });
            }

#pragma warning disable CS0168 // 声明了变量，但从未使用过
            catch (Exception e)
#pragma warning restore CS0168 // 声明了变量，但从未使用过
            {

            }
        }

        private void InitTime()
        {
            System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
            timer.Interval = 1000;
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void InitProjectInfo()
        {
            ProcessModule processModule = Process.GetCurrentProcess().MainModule;
            string path = Path.GetDirectoryName(processModule.FileName);
            this.projectsPath = Path.Combine(path, "projects");
            if (!Directory.Exists(this.projectsPath))
            {
                Directory.CreateDirectory(this.projectsPath);
            }

            string[] projectPaths = Directory.GetDirectories(this.projectsPath);
            List<string> projectList = new List<string>();
            foreach (var temp in projectPaths)
            {
                DirectoryInfo directoryInfo = new DirectoryInfo(temp);
                projectList.Add(directoryInfo.Name);
            }

            this.tscbProject.ComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            this.tscbProject.ComboBox.DataSource = projectList;
            this.tscbProject.ComboBox.SelectedIndexChanged += ComboBox_SelectedIndexChanged;
        }

        private void ComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!this.tscbProject.ComboBox.Enabled)
            {
                return;
            }

            foreach (var content in this.dockPanel.Contents)
            {
                FormMain formMain = content as FormMain;
                if (formMain != null)
                {
                    WinApi.PostMessage(formMain.Handle, WinApi.WM_CLOSE, IntPtr.Zero, IntPtr.Zero);
                }
            }

            if (this.tscbProject.ComboBox.Text.Contains("WIFI"))
            {
                try
                {
                    ProcessStartInfo psi = new ProcessStartInfo();
                    psi.FileName = "WLAN Facility.exe";
                    psi.UseShellExecute = false;
                    psi.CreateNoWindow = true;
                    Process.Start(psi);
                    this.Close();

                }
                catch (Exception ex)
                {

                    MessageBox.Show("启动性能测试失败:" + ex.Message);
                }

                //Process proc = Process.Start("WLAN Facility.exe");

                return;
            }
            DirectoryInfo directoryInfo = new DirectoryInfo(
                Path.Combine(this.projectsPath, this.tscbProject.ComboBox.Text));
            List<Dut> dutList = new List<Dut>();
            foreach (var fileInfo in directoryInfo.GetFiles())
            {
                Dut dut = Dut.GenDut(fileInfo.FullName.Replace(ProcessUtils.GetAppPath(), ""));
                dutList.Add(dut);
            }

            foreach (var dut in dutList)
            {
                FormMain formMain = new FormMain();
                formMain.ResultProperties = this.resultProperties;
                formMain.Remark = dut.FileName;
                formMain.StartHandler = this.StartHandler;
                formMain.StopHandler = this.StopHandler;
                formMain.Show(this.dockPanel, DockState.Document);
                formMain.Activate();
            }
        }

        private void TsmSaveLayout_Click(object sender, EventArgs e)
        {
            //this.dockPanel.SaveAsXml(filenameLayout, Encoding.UTF8);
            this.dockPanel.SaveAsXmlRemark(filenameLayout, Encoding.UTF8);
            LogUtils.UiInfo.Info(string.Format("save layout {0} success", filenameLayout));
            Box.ShowInfoOk(string.Format("save layout {0} success", filenameLayout));
            this.tscbProject.ComboBox.Enabled = false;
        }

        private void TsmPaint_Click(object sender, EventArgs e)
        {
            LogUtils.UiInfo.Info("open paint");
            Process.Start("msPaint.exe");
        }

        private void TsmNote_Click(object sender, EventArgs e)
        {
            LogUtils.UiInfo.Info("open notepad");
            Process.Start("notepad.exe");
        }
        private void TsmVerify_Click(object sender, EventArgs e)
        {
            LogUtils.UiInfo.Info("open WtCableVerifyTool");
            try
            {
                Process.Start("WtCableVerifyTool.exe");
            }
            catch (Exception ex)
            {

                MessageBox.Show(ex.Message);
            }
        }
        private void TsmCalc_Click(object sender, EventArgs e)
        {
            LogUtils.UiInfo.Info("open calc");
            Process.Start("calc.exe");
        }

        private void TsmAbout_Click(object sender, EventArgs e)
        {
            new FormAbout().ShowDialog();
        }

        private void TsmExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            this.tsslTime.Text = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        }

        private void FormStudio_Shown(object sender, EventArgs e)
        {
            tsbpProgress.Value = 0;
            LoadProject();
            LogUtils.UiInfo.Info("\r\n           _____ _      _       _    ______         _                                 _        _____ _             _ _       \r\n     /\\   |_   _| |    (_)     | |  |  ____|       | |                     /\\        | |      / ____| |           | (_)      \r\n    /  \\    | | | |     _ _ __ | | _| |__ __ _  ___| |_ ___  _ __ _   _   /  \\  _   _| |_ ___| (___ | |_ _   _  __| |_  ___  \r\n   / /\\ \\   | | | |    | | \'_ \\| |/ /  __/ _` |/ __| __/ _ \\| \'__| | | | / /\\ \\| | | | __/ _ \\\\___ \\| __| | | |/ _` | |/ _ \\ \r\n  / ____ \\ _| |_| |____| | | | |   <| | | (_| | (__| || (_) | |  | |_| |/ ____ \\ |_| | || (_) |___) | |_| |_| | (_| | | (_) |\r\n /_/    \\_\\_____|______|_|_| |_|_|\\_\\_|  \\__,_|\\___|\\__\\___/|_|   \\__, /_/    \\_\\__,_|\\__\\___/_____/ \\__|\\__,_|\\__,_|_|\\___/ \r\n                                                                   __/ |                                                     \r\n                                                                  |___/                                                      \r\n");
            string version = "V1.01";
            this.tsslVersion.Text = "东莞市华复实业有限公司-万魔声学PCBA自动测试系统" + " " + version;
            this.Text = "东莞市华复实业有限公司-万魔声学PCBA自动测试系统";
            LogUtils.UiInfo.Info(tsslVersion.Text);
            LogUtils.UiInfo.Info("V1.02");
            tsbpProgress.Value = 100;
        }

        private void LoadProject()
        {
            if (File.Exists(filenameLayout))
            {
                this.tscbProject.ComboBox.Enabled = false;

                this.dockPanel.LoadFromXml(filenameLayout, deserializeContent =>
                {
                    string typName;
                    Assembly assembly = Assembly.GetExecutingAssembly();
                    string[] contents = deserializeContent.Split(new char[] {','}, StringSplitOptions.RemoveEmptyEntries);
                    typName = contents[0];
                    DockContent dockContent = assembly.CreateInstance(typName) as DockContent;

                    if (contents.Length == 2)
                    {
                        IDockRemark remark = dockContent as IDockRemark;
                        remark.Remark = contents[1];
                        Dut dut = Dut.GenDut(contents[1]);
                        this.tscbProject.ComboBox.Text = dut.ProjectName;

                        IRunnable runnable = dockContent as IRunnable;
                        runnable.StartHandler = this.StartHandler;
                        runnable.StopHandler = this.StopHandler;
                    }

                    return dockContent;
                });
            }
            else
            {
                DirectoryInfo directoryInfo = new DirectoryInfo(
                    Path.Combine(this.projectsPath, this.tscbProject.ComboBox.Text));
                List<Dut> dutList = new List<Dut>();
                foreach (var fileInfo in directoryInfo.GetFiles())
                {
                    Dut dut = Dut.GenDut(fileInfo.FullName);
                    dutList.Add(dut);
                }

                FormInfo formInfo = new FormInfo();
                formInfo.Show(this.dockPanel, DockState.DockBottom);

                FormLog formLog = new FormLog();
                formLog.Show(this.dockPanel, DockState.DockBottom);
                formInfo.Activate();

                string appPath = ProcessUtils.GetAppPath();
                foreach (var dut in dutList)
                {
                    FormMain formMain = new FormMain();
                    formMain.ResultProperties = this.resultProperties;
                    formMain.Remark = dut.FileName.Replace(appPath, "");
                    formMain.StartHandler = this.StartHandler;
                    formMain.StopHandler = this.StopHandler;
                    formMain.Show(this.dockPanel, DockState.Document);
                    formMain.Activate();
                }
            }
        }

        private void StartHandler()
        {
            int count = Dut.GetCount();
            if (count == 0)
            {            
                stopWatch.Start();
            }

            Dut.Inc();
        }

        private void StopHandler(bool result)
        {
            int count = Dut.Dec();
            if (count == 0)
            {
                stopWatch.Stop();
            }

            if (result)
            {
                this.resultProperties.IncPass();
            }
            else
            {
                this.resultProperties.IncFail();
            }

            if (StudioProperties.AutoStart)
            {
                //this.Invoke((EventHandler)delegate
                //{
                //    PostMessage(this.Handle, WM_USER_AUTOSTART, 0, 0);
                //});
                new Thread(e =>
                {
                    for (int i = 0; i < 100 && StudioProperties.AutoStart; i++)
                    {
                        try
                        {
                            this.Invoke((EventHandler)delegate
                            {
                                Start();
                            });
                            break;
                        }
                        catch (Exception)
                        {
                            Thread.Sleep(100);
                        }
                    }
                }).Start();
            }
            else
            {
                this.Invoke((EventHandler)delegate
                {
                    this.tsbStart.Enabled = true;
                });
            }
        }

        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)
            {
                case WM_USER_AUTOSTART:
                    //for (int i = 0; i < 100; i++)
                    //{
                    //    try
                    //    {
                    //        Start();
                    //        LogUtils.UiInfo.Info("Start Success!");
                    //        break;
                    //    }
                    //    catch (Exception e)
                    //    {
                    //        LogUtils.UiInfo.Info(e.Message);
                    //    }

                    //    Thread.Sleep(100);
                    //}
                    break;

                default:
                    base.WndProc(ref m);
                    break;
            }
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            switch (keyData)
            {
                case Keys.Enter:
                    TsbStart_Click(null, null);
                    return true;

                default:
                    return base.ProcessCmdKey(ref msg, keyData);
            }        
        }


        private void SetInstruction_Click(object sender, EventArgs e)
        {
            FormInstruction form = new FormInstruction();
            form.Show();
        }
    }
}
