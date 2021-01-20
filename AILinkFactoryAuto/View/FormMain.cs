using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Properties;
using AILinkFactoryAuto.Task;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.Utils;
using WeifenLuo.WinFormsUI.Docking;
using System.Drawing;
using AILinkFactoryAuto.Common;
using AILinkFactoryAuto.Peripherals;

namespace AILinkFactoryAuto.View
{
    public partial class FormMain : DockContent, IDockRemark, IRunnable
    {
        [DllImport("user32.dll")]
        private static extern int BringWindowToTop(IntPtr hWnd);

        public string ThreadName
        {
            get { return dut.Name; }
            set { dut.Name = value; }
        }

        //private static string COLUMN_NAME_SELECT = "SELECT";
        private static string COLUMN_NAME_ITEM = "ITEM";
        //private static string COLUMN_NAME_SELECT_VALUE = "IsChecked";


        public StartHandler StartHandler { get; set; }

        public StopHandler StopHandler { get; set; }

        private Dut dut;

        public string Remark { get; set; }

        private bool isRunning;

        public bool IsRunning
        {
            get { return this.isRunning; }
        }

        public CountLatch Sync { get; set; }

        private static string signPass = @"
     PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
     PP                                                                   PP
     PP                 PPPPPPPP     PPP     PPPPPP   PPPPPP              PP
     PP                 PP     PP   PP PP   PP    PP PP    PP             PP
     PP                 PP     PP  PP   PP  PP       PP                   PP
     PP                 PPPPPPPP  PP     PP  PPPPPP   PPPPPP              PP
     PP                 PP        PPPPPPPPP       PP       PP             PP
     PP                 PP        PP     PP PP    PP PP    PP             PP
     PP                 PP        PP     PP  PPPPPP   PPPPPP              PP
     PP                                                                   PP
     PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
";
        private static string signFail = @"
     FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
     FF                                                                   FF
     FF                    FFFFFFFF    FFF     FFFF  FF                   FF
     FF                    FF         FF FF     FF   FF                   FF
     FF                    FF        FF   FF    FF   FF                   FF
     FF                    FFFFFF   FF     FF   FF   FF                   FF
     FF                    FF       FFFFFFFFF   FF   FF                   FF
     FF                    FF       FF     FF   FF   FF                   FF
     FF                    FF       FF     FF  FFFF  FFFFFFFF             FF
     FF                                                                   FF
     FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
";

        private List<TaskItem> taskItemList;

        private string jtsFileName;

        private JsonTestSequence jsonTestSequence = new JsonTestSequence();

        private Robot robot = new Robot();

        private ResultProperties resultProperties;

        public ResultProperties ResultProperties
        {
            get { return resultProperties; }
            set { resultProperties = value; }
        }

        public FormMain()
        {            
            InitializeComponent();
        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            dut = Dut.GenDut(Remark);

            this.Text = dut.Name;
            this.Icon = Resources.phone;

            this.picSettings.Parent = this.progressBar1;
            this.picSettings.Location = new Point(
                this.picSettings.Location.X,
                this.picSettings.Location.Y - 10);
            this.picSettings.BackgroundImage = Resources.setup;
            this.picSettings.BackgroundImageLayout = ImageLayout.Stretch;
            this.picSettings.Click += PicSettings_Click;
            this.label1.Parent = this.progressBar1;
            this.label1.Location = new Point(
                this.label1.Location.X,
                this.label1.Location.Y - 10);

            this.rtxLog.ReadOnly = true;
            this.rtxLog.WordWrap = false;

            this.Shown += FormMain_Shown;
            this.FormClosing += FormMain_FormClosing;
            this.FormClosed += FormMain_FormClosed;
            this.txtSn.KeyPress += TxtSn_KeyPress;

            InitDataGridView();

        }

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (isRunning)
            {
                e.Cancel = true;
                Box.ShowInfoOk("工作线程正在运行......");
            }
        }

        private void InitDataGridView()
        {
            dataGridView.ReadOnly = true;
            dataGridView.CurrentCell = null;
            //dataGridView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            //dataGridView.EditMode = DataGridViewEditMode.EditOnEnter;
            dataGridView.MultiSelect = false;
            dataGridView.BackgroundColor = Color.WhiteSmoke;
            dataGridView.RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode.AutoSizeToAllHeaders;
            dataGridView.AllowUserToAddRows = false;

            //DataGridViewCheckBoxColumn chkSelect = new DataGridViewCheckBoxColumn();
            //chkSelect.Name = COLUMN_NAME_SELECT;
            //chkSelect.HeaderText = "SELECT";
            //chkSelect.TrueValue = true;
            //chkSelect.FalseValue = false;
            //chkSelect.DataPropertyName = COLUMN_NAME_SELECT_VALUE;
            //dataGridView.Columns.Add(chkSelect);
            //dataGridView.Columns[0].Frozen = true;

            DataGridViewTextBoxColumn txtItem = new DataGridViewTextBoxColumn();
            txtItem.Name = COLUMN_NAME_ITEM;
            txtItem.HeaderText = "测试项目";
            dataGridView.Columns.Add(txtItem);
            dataGridView.Columns[0].Frozen = true;

            dataGridView.Columns[0].SortMode = DataGridViewColumnSortMode.NotSortable;
            dataGridView.Columns[0].AutoSizeMode = DataGridViewAutoSizeColumnMode.DisplayedCells;
            //dataGridView.Columns[1].SortMode = DataGridViewColumnSortMode.NotSortable;
            //dataGridView.Columns[1].AutoSizeMode = DataGridViewAutoSizeColumnMode.DisplayedCells;

            //dataGridView.Columns[0].SortMode = DataGridViewColumnSortMode.NotSortable;
            //dataGridView.Columns[0].AutoSizeMode = DataGridViewAutoSizeColumnMode.DisplayedCells;

        }

        private void DisplayFlow(List<TaskItem> baseFlowList)
        {
            dataGridView.Rows.Clear();
            if (baseFlowList == null)
            {
                return;
            }

            for (int i = 0; i < baseFlowList.Count; i++)
            {
                if (baseFlowList[i].Enable)
                {
                    int index = dataGridView.Rows.Add();
                    //dataGridView.Rows[index].Cells[COLUMN_NAME_SELECT].Value = baseFlowList[i].Enable;
                    dataGridView.Rows[index].Cells[COLUMN_NAME_ITEM].Value = baseFlowList[i].Item;
                }
                //dataGridView.Rows[index].Cells[COLUMN_NAME_ITEM].ToolTipText = baseFlowList[i].Tip;
            }
        }

        private void TxtSn_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != (int)Keys.Enter)
            {
                return;
            }

            lock (this)
            {
                if (isRunning)
                {
                    Box.ShowErrorOk("工作线程正在运行......");
                    return;
                }

                isRunning = true;

                new Thread(Run)
                {
                    Name = "Thread-" + dut.Name,
                    IsBackground = true
                }.Start();
            }
        }

        private void FormMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            //Application.Exit();
            //Environment.Exit(0);
        }

        private void FormMain_Shown(object sender, EventArgs e)
        {
            LogUtils.UiInfo.Info(this.Text);

            jtsFileName = dut.FileName;
            LogUtils.UiInfo.InfoFormat("加载测试序列=[{0}]", dut.FileName);
            LoadJts();

            LogUtils.UiInfo.Info("FormMain................Success!");



            string[] jsonFileList = jsonTestSequence.GetAllJsonFiles(ProcessUtils.GetAppPath() + dut.ProjectPath);
            for (int i = 0; i < jsonFileList.Length; i++)
            {
                TreeNode node = new TreeNode(jsonFileList[i]);
                string filename = Path.GetFileName(jtsFileName);
                if (!string.IsNullOrEmpty(filename) && filename.Equals(jsonFileList[i]))
                {
                    node.ForeColor = Color.Green;
                    node.Checked = true;
                    taskItemList = jsonTestSequence.GetTaskItemListFromFileName(ProcessUtils.GetAppPath() + dut.ProjectPath, node.Text);
                    DisplayFlow(taskItemList);
                }
            }
            this.dataGridView.ClearSelection();


        }

        private void LoadJts()
        {
            try
            {
                toolStripStatusLabel.Text = "测试序列：" + dut.FileName;               
                taskItemList = jsonTestSequence.GetTaskItemListFromFullFileName(
                    ProcessUtils.GetAppPath() + dut.FileName);
                if (taskItemList == null)
                {
                    Box.ShowInfoOk("测试序列加载失败\r\n" + "请检查" + dut.FileName + "是否存在");
                    LogUtils.UiInfo.Error("测试序列加载失败\r\n" + "请检查" + dut.FileName + "是否存在");
                }
                else
                {
                    LogUtils.UiInfo.Info("加载测试序列成功");
                }
            }
            catch (Exception e)
            {
                LogUtils.UiInfo.Error(e.ToString());
                Box.ShowInfoOk(e.Message);
            }
        }

        public void Stop()
        {
            this.isRunning = false;
            if (this.robot != null)
            {
                this.robot.Enable = false;
            }
        }

        public void Start()
        {
            this.isRunning = true;
            this.robot.Enable = true;
        }

        public void Run()
        {
            bool result = true;
            string allTime = null;
            string labelSn = null;
            try
            {
                if (StudioProperties.EnableRobot)
                {
                    this.robot.Start();
                    labelSn = this.robot.GetSn();
                }

                if (StartHandler != null)
                {
                    StartHandler();
                }

                if (taskItemList == null)
                {
                    Box.ShowInfoOk("测试流程为空");
                    return;
                }

                TestTime allTestTime = new TestTime();
                allTestTime.StartRecord();
                Init();

                GlobalDic<string, object> globalDic = new GlobalDic<string, object>();
                ILog log = new Log(rtxLog);
                Limit limit = new Limit(log);
                globalDic.Put(limit);

                GlobalVaribles configGv = new GlobalVaribles();
                if (StudioProperties.EnableRobot)
                {
                    configGv.Add(GlobalVaribles.LABEL_SN, labelSn);
                }
                else
                {
                    configGv.Add(GlobalVaribles.LABEL_SN, txtSn.Text);
                }
                configGv.Form = this;

                globalDic.Put<CountLatch>(Sync);
                globalDic.Put<ILog>(log);
                globalDic.Put(configGv);

                string title =
                    @"
     ***********************************************************************
     ***********************************************************************
     ***********                                                  **********
     ***********                  FactoryAuto                     **********
     ***********                  Huafuu                          **********
     ***********                                                  **********
     ***********                                                  **********
     ***********************************************************************
     ***********************************************************************";
                string testDay = DateTime.Now.ToString("yyyy-MM-dd");
                string testTime = DateTime.Now.ToString("HH:mm:ss");
                title += "\r\n     Test Date: " + testDay +
                         ", Test Time: " + testTime + "\r\n\r\n";
                log.Info(title);

                string errorlog = "";
                //进度条和lable显示
                Progress progress = new Progress(progressBar1, label1);
                progress.SetProgressMinMax(0, taskItemList.Count);

                for (int i = 0; i < taskItemList.Count; i++)
                {
                    if (!isRunning)
                    {
                        result = false;
                        break;
                    }

                    //开始测试时间
                    DateTime startTestTime = DateTime.Now;

                    //加载进度条和lable显示
                    if(result)
                    {
                        progress.SetProgress(i);
                    }

                    if (!taskItemList[i].Enable)
                    {
                        continue;
                    }

                    TaskItem taskItem = taskItemList[i];
                    CommonProperties commonProperties = taskItem.CommonProperties;
                    log.Info(string.Format("{0} {1}", i + 1, taskItem.Item));
                    int retry = commonProperties.RetryCount;
                    uint retryCount = 0;
                    bool resultNow = false;
                    do
                    {
                        try
                        {
                            if (taskItem.Executer != null)
                            {
                                if (result && commonProperties.ExecuteCondition == ExecuteCondition.PASS)
                                {
                                    Thread.Sleep(commonProperties.SleepTimeBefore);
                                    taskItem.Executer.Run(taskItem.CommonProperties, globalDic);
                                    Thread.Sleep(commonProperties.SleepTimeAfter);
                                }
                                else if (commonProperties.ExecuteCondition == ExecuteCondition.ALWAYS)
                                {
                                    Thread.Sleep(commonProperties.SleepTimeBefore);
                                    taskItem.Executer.Run(taskItem.CommonProperties, globalDic);
                                    Thread.Sleep(commonProperties.SleepTimeAfter);
                                }

                                resultNow = true;
                                break;
                            }
                        }
                        catch (Exception e)
                        {
                            resultNow = false;
                            log.Info(e.Message);
                            LogUtils.UiDebug.Error(e.ToString()); 
                            if (retry == 0 && !errorlog.Contains(e.ToString()) && !errorlog.Contains("项:\r\n"))
                            {
                                errorlog = "\r\n" + "第" + (i + 1).ToString() + "项:\r\n" + taskItem.Item + "\r\n" +
                                           e.ToString() + "\r\n";
                            }
                        }

                        Thread.Sleep(commonProperties.RetryInterval);

                        retry--;
                        retryCount++;
                        if (retry >= 0)
                        {
                            log.Warn("重试第" + retryCount + "次");
                        }
                    } while (retry >= 0 && this.isRunning);

                    if (result == false && commonProperties.ExecuteCondition == ExecuteCondition.PASS)
                    {
                        log.Warn("TestTime:" + (DateTime.Now - startTestTime).TotalMilliseconds + "ms"
                                 + Environment.NewLine +
                                 "                                                                        SKIP");
                    }
                    else if (!resultNow)
                    {
                        result = false;
                        log.Fail("TestTime:" + (DateTime.Now - startTestTime).TotalMilliseconds + "ms"
                                 + Environment.NewLine +
                                 "                                                                        FAIL");
                    }
                    else
                    {
                        log.Pass("TestTime:" + (DateTime.Now - startTestTime).TotalMilliseconds + "ms"
                                 + Environment.NewLine +
                                 "                                                                        PASS");
                    }

                    //加载进度条和lable显示
                    progress.SetProgress(i + 1);
                }

                if (result)
                {
                    log.Pass(signPass);
                }
                else
                {
                    log.Fail(signFail);
                }

                log.Fail(errorlog);
                allTime = allTestTime.StopRecord();
                log.Info(string.Format("all test time:{0}", allTime));

                DeinitProperties configDeinit = globalDic.Get<DeinitProperties>();
                if (configDeinit.LogType == LogType.IMEI)
                {
                    //日志输出到文件 IMEI-ICCID-IMSI-EID-SN-MAC-NFC-SSID-MEID
                    //日志输出到文件 IMEI-ICCID-IMSI-EID-SN-MAC-NFC-SSID   
                    string sn = string.Format("{0}-{1}-{2}-{3}-{4}-{5}-{6}-{7}",
                        configGv.Get(GlobalVaribles.IMEI),
                        configGv.Get(GlobalVaribles.ICCID),
                        configGv.Get(GlobalVaribles.IMSI),
                        configGv.Get(GlobalVaribles.EID),
                        configGv.Get(GlobalVaribles.SN),
                        configGv.Get(GlobalVaribles.MAC),
                        configGv.Get(GlobalVaribles.NFC),
                        configGv.Get(GlobalVaribles.SSID));
                    if (result)
                    {
                        FileUtil.fwrite("./log/PASS/",
                            sn + "_" + testDay.Replace("-", "") + "_" + testTime.Replace(":", "") + "_PASS.log",
                            ((Log) log).LogFileMessage);
                    }
                    else
                    {
                        FileUtil.fwrite("./log/FAIL/",
                            sn + "_" + testDay.Replace("-", "") + "_" + testTime.Replace(":", "") + "_FAIL.log",
                            ((Log) log).LogFileMessage);
                    }
                }
                else if (configDeinit.LogType == LogType.MAC)
                {
                    //string sn = string.Format("{0}", configGv.Get(GlobalVaribles.MAC));
                    string sn = string.Format("{0}-{1}-{2}-{3}-{4}-{5}-{6}-{7}-{8}-{9}",
                        configGv.Get(GlobalVaribles.MAC),
                        configGv.Get(GlobalVaribles.IMEI),
                        configGv.Get(GlobalVaribles.SN),
                        configGv.Get(GlobalVaribles.ICCID),
                        configGv.Get(GlobalVaribles.IMSI),
                        configGv.Get(GlobalVaribles.EID),
                        configGv.Get(GlobalVaribles.NFC),
                        configGv.Get(GlobalVaribles.SSID),
                        configGv.Get(GlobalVaribles.TBSN),
                        configGv.Get(GlobalVaribles.POWERSN));
                    if (result)
                    {
                        FileUtil.fwrite("./log/PASS/",
                            sn + "_" + testDay.Replace("-", "") + "_" + testTime.Replace(":", "") + "_PASS.log",
                            ((Log) log).LogFileMessage);
                    }
                    else
                    {
                        FileUtil.fwrite("./log/FAIL/",
                            sn + "_" + testDay.Replace("-", "") + "_" + testTime.Replace(":", "") + "_FAIL.log",
                            ((Log) log).LogFileMessage);
                    }
                }
                else if (configDeinit.LogType == LogType.SN)
                {
                    //日志输出到文件 IMEI-ICCID-IMSI-EID-SN-MAC-NFC-SSID-MEID
                    //日志输出到文件 IMEI-ICCID-IMSI-EID-SN-MAC-NFC-SSID   
                    string sn = "";
                    if (!string.IsNullOrEmpty(configGv.Get(GlobalVaribles.SN)))
                    {
                         sn = string.Format("{0}",
                            configGv.Get(GlobalVaribles.SN));
                    }
                    if (result)
                    {
                        FileUtil.fwrite("./log/PASS/",
                            sn + "_" + testDay.Replace("-", "") + "_" + testTime.Replace(":", "") + "_PASS.log",
                            ((Log)log).LogFileMessage);
                    }
                    else
                    {
                        FileUtil.fwrite("./log/FAIL/",
                            sn + "_" + testDay.Replace("-", "") + "_" + testTime.Replace(":", "") + "_FAIL.log",
                            ((Log)log).LogFileMessage);
                    }
                }
                else
                {
                    throw new BaseException("不支持此类型的LOG");
                }

                if (result)
                {
                    progress.SetBrush(Brushes.Green);
                }
                else
                {
                    progress.SetBrush(Brushes.Red);
                }

                Deinit(result);
            }
            catch (Exception e)
            {
                LogUtils.UiDebug.Error(e.ToString());
            }
            finally
            {
                this.isRunning = false;

                if (StopHandler != null)
                {
                    StopHandler(result);
                }

                if (StudioProperties.EnableRobot)
                {
                    this.robot.CreateStates(result, 
                        resultProperties.Pass, 
                        resultProperties.Fail,
                        allTime, 
                        "code_01", 
                        "fail");
                }
            }            
        }

        private void Deinit(bool result)
        {
            this.Invoke((EventHandler) delegate
            {
                if (result)
                {
                    txtSn.BackColor = Color.Green;
                }
                else
                {
                    txtSn.BackColor = Color.Red;
                }
                txtSn.Text = null;
                txtSn.ReadOnly = false;
                txtSn.Focus();
                BringWindowToTop(this.Handle);
            });
        }

        private void Init()
        {
            this.Invoke((EventHandler)delegate
            {
                txtSn.ReadOnly = true;
                rtxLog.Text = null;
            });
        }

        private void PicSettings_Click(object sender, EventArgs e)
        {
#if DEBUG

#else

            FormLogin formLogin = new FormLogin();
            DialogResult dialogResult = formLogin.ShowDialog();
            if (dialogResult != DialogResult.OK)
            {
                return;
            }
#endif

            FormProperties formProperties = new FormProperties()
            {
                JsonTestSequence = jsonTestSequence,
                JtsFileName = jtsFileName
            };
            formProperties.ShowDialog();
            LoadJts();

            FormMain_Shown(null, null);
        }
    }
}
