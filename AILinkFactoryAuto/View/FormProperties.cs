using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Properties;
using AILinkFactoryAuto.Task;
using WeifenLuo.WinFormsUI.Docking;
using AILinkFactoryAuto.Utils;
using MySql.Data.MySqlClient;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using AILinkFactoryAuto.Core.HttpClient;
using System.Net;

namespace AILinkFactoryAuto.View
{
    public partial class FormProperties : Form
    {
        private static string COLUMN_NAME_SELECT = "SELECT";
        private static string COLUMN_NAME_ITEM = "ITEM";
        private static string COLUMN_NAME_SELECT_VALUE = "IsChecked";

        private List<TaskItem> taskItemList;
        private string jtsFileName;
        private JsonTestSequence jsonTestSequence;

        private Dut dut;

        private ContextMenuStrip contextMenuStrip1;
        private int selectRowIndex;
        private TaskItem selectTaskItem;

        public string JtsFileName
        {
            set { jtsFileName = value; }
        }

        public JsonTestSequence JsonTestSequence
        {
            set { jsonTestSequence = value; }
        }

        public FormProperties()
        {
            InitializeComponent();
        }

        private void FormProperties_Load(object sender, EventArgs e)
        {
            this.Icon = Resources.logo1;

            this.Shown += FormProperties_Shown;
            this.Closed += FormProperties_Closed;

            treeView.CheckBoxes = true;
            treeView.AfterCheck += TreeView_AfterCheck;

            dut = Dut.GenDut(jtsFileName);

            InitContextMenuStrip();

            InitDataGridView();

            //tsmGenJts.Click += TsmGenJts_Click;
            tsmSelectAll.Click += TsmSelectAll_Click;
            tsmSelctNone.Click += TsmSelctNone_Click;
        }

        //private void TsmGenJts_Click(object sender, EventArgs e)
        //{
        //    OpenFileDialog openFileDialog = new OpenFileDialog();
        //    openFileDialog.Multiselect = false;
        //    openFileDialog.InitialDirectory = Environment.CurrentDirectory;
        //    openFileDialog.Title = "生成测试序列";
        //    openFileDialog.Filter = "测试序列(AILinkFactoryAuto.GenJts.*.dll)|AILinkFactoryAuto.GenJts.*.dll";
        //    DialogResult dialogResult = openFileDialog.ShowDialog();
        //    if (dialogResult == DialogResult.OK)
        //    {
        //        Assembly assembly = Assembly.LoadFrom(openFileDialog.FileName);
        //        Type[] types = assembly.GetTypes();
        //        foreach (Type type in types)
        //        {
        //            bool isForm = type.IsSubclassOf(typeof(Form));
        //            if (isForm)
        //            {
        //                Form form = Activator.CreateInstance(type) as Form;
        //                form.StartPosition = FormStartPosition.CenterScreen;
        //                form.ShowDialog();
        //                FormProperties_Shown(null, null);
        //            }
        //        }
        //    }         
        //}

        private void TsmSelctNone_Click(object sender, EventArgs e)
        {
            foreach (var taskItem in taskItemList)
            {
                taskItem.Enable = false;
            }
            DisplayFlow(taskItemList);
        }

        private void TsmSelectAll_Click(object sender, EventArgs e)
        {
            foreach (var taskItem in taskItemList)
            {
                taskItem.Enable = true;
            }
            DisplayFlow(taskItemList);
        }

        //private void TsmCableLossFt_Click(object sender, EventArgs e)
        //{
        //    FormCableLoss formCableLoss = new FormCableLoss();
        //    formCableLoss.TaskItemList = this.taskItemList;
        //    formCableLoss.ShowDialog();

        //    this.propertyGrid.SelectedObject = null;
        //    //FormProperties_Shown(null, null);
        //}

        //private void tsmCableLossBt_Click(object sender, EventArgs e)
        //{
        //    FormCableLossBt formCableLossBt = new FormCableLossBt();
        //    //屏幕居中显示
        //    formCableLossBt.StartPosition = FormStartPosition.CenterScreen;
        //    //子窗口的不关闭时，其它的窗口无法操作
        //    formCableLossBt.ShowDialog();
        //}

        //private void TsmGenJtsMdm9x07_Click(object sender, EventArgs e)
        //{
        //    FormJtsMdm9x07 formJtsMdm9X07 = new FormJtsMdm9x07();
        //    formJtsMdm9X07.JsonTestSequence = this.jsonTestSequence;
        //    formJtsMdm9X07.ShowDialog();
        //    FormProperties_Shown(null, null);
        //}

        private void FormProperties_Closed(object sender, EventArgs e)
        {
            UpdateCheckBox();
            jsonTestSequence.SaveJsonFile(ProcessUtils.GetAppPath() + jtsFileName, taskItemList);

#if DEBUG

#else
            //try
            //{
            //    MachineInfoUtils machineInfo = new MachineInfoUtils();
            //    string hostName=machineInfo.GetHostName();
            //    string cpuSerialNumber=machineInfo.GetCPUSerialNumber();
            //    string systemType = machineInfo.GetSystemType();
                
            //    //登录信息
            //    AILinkFactoryAuto.Utils.LoginInfoUtils.Root loginRep =  JsonConvert.DeserializeObject(FormLogin.LoginInfo, typeof(AILinkFactoryAuto.Utils.LoginInfoUtils.Root)) as AILinkFactoryAuto.Utils.LoginInfoUtils.Root;

            //    string jtsFileContent = jsonTestSequence.GetJsonFile(taskItemList);
            //    string sqlInsert = "INSERT INTO modifylog (`loginname`,`name`, `phone`, `email`,`hostname`,`systemtype`,`cpuserialnumber`,`jtschangelog`)VALUES ('{0}', '{1}', '{2}','{3}','{4}','{5}','{6}','{7}');";
            //    //sqlInsert = string.Format(sqlInsert, sn, uid, order, System.DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss"));//yyyy-MM-dd hh:mm:ss
            //    jtsFileContent = jtsFileContent.Substring(0, 200);
            //    sqlInsert = string.Format(sqlInsert,loginRep.loginName, loginRep.name, loginRep.phone, loginRep.email, hostName,systemType, cpuSerialNumber, jtsFileContent);

            //    MySqlUtils mySql = new MySqlUtils();
            //    MySqlConnection myConn=mySql.GetConn();
            //    mySql.Insert(sqlInsert, myConn);
            //    mySql.CloseConn();
            //}
            //catch (Exception ex)
            //{
            //    MessageBox.Show(ex.Message);
            //}
            #region 数据上传
            //上传数据:用户名,手机,邮箱,日期,PC信息，最新的jts文件内容
            try
            {
                MachineInfoUtils machineInfo = new MachineInfoUtils();
                string hostName = machineInfo.GetHostName();
                string cpuSerialNumber = machineInfo.GetCPUSerialNumber();
                string systemType = machineInfo.GetSystemType();

                //登录返回信息反序列化
                AILinkFactoryAuto.Utils.LoginInfoUtils.Root loginRep = JsonConvert.DeserializeObject(FormLogin.LoginInfo, typeof(AILinkFactoryAuto.Utils.LoginInfoUtils.Root)) as AILinkFactoryAuto.Utils.LoginInfoUtils.Root;
                string jtsFileContent = jsonTestSequence.GetJsonFile(taskItemList);

                JObject param = new JObject();
                param.Add("loginName", loginRep.loginName);
                param.Add("name", loginRep.name);
                param.Add("phone", loginRep.phone);
                param.Add("email", loginRep.email);
                param.Add("hostName", hostName);
                param.Add("systemType", systemType);
                param.Add("cpuSerialNumber", cpuSerialNumber);
                param.Add("jtsChangeLog", jtsFileContent);
                RestClient restClient = new RestClient();
                restClient.ContentType = new ContentType("application/json", "utf-8");//"application/json";
                IRestResponse iRestResponse = restClient.Post(StudioProperties.UrlUploadModifyJts, param.ToString());


                if (!(iRestResponse.GetHttpStatusCode() == HttpStatusCode.OK))
                {
                    MessageBox.Show(iRestResponse.GetErrorMessage());
                }
                if (!iRestResponse.GetResponseBody().Contains("200"))
                {
                    MessageBox.Show(iRestResponse.GetErrorMessage());
                }
                if (!iRestResponse.GetResponseBody().Contains("success"))
                {
                    MessageBox.Show(iRestResponse.GetErrorMessage());
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            #endregion

#endif
        }

        private void TreeView_AfterCheck(object sender, TreeViewEventArgs e)
        {
            if (e.Action == TreeViewAction.ByMouse)
            {
                foreach (TreeNode node in treeView.Nodes)
                {
                    node.Checked = false;
                    node.ForeColor = ForeColor;
                }

                e.Node.Checked = true;
                e.Node.ForeColor = Color.Green;

                UpdateCheckBox();
                propertyGrid.SelectedObject = null;
                jsonTestSequence.SaveJsonFile(jtsFileName, taskItemList);

                jtsFileName = e.Node.Text;
                taskItemList = jsonTestSequence.GetTaskItemListFromFileName(dut.ProjectPath, e.Node.Text);
                DisplayFlow(taskItemList);
            }
        }
        private void InitContextMenuStrip()
        {
            // contextMenuStrip1
            // 
            // 
            // tstbCopy
            // 
            ToolStripMenuItem tstbCopy = new System.Windows.Forms.ToolStripMenuItem();
            tstbCopy.Name = "tstbCopy";
            tstbCopy.Text = "复制";
            //resources.ApplyResources(this.tstbCopy, "tstbCopy");
            tstbCopy.Click += new System.EventHandler(tstbCopy_Click);
            // 
            // tstbPaste
            // 
            ToolStripMenuItem tstbPaste = new System.Windows.Forms.ToolStripMenuItem();
            tstbPaste.Name = "tstbPaste";
            tstbPaste.Text = "粘贴";
            //resources.ApplyResources(this.tstbPaste, "tstbPaste");
            tstbPaste.Click += new System.EventHandler(tstbPaste_Click);
            // 
            // tstbDelete
            // 
            ToolStripMenuItem tstbDelete = new System.Windows.Forms.ToolStripMenuItem();
            tstbDelete.Name = "tstbDelete";
            tstbDelete.Text = "删除";
            //resources.ApplyResources(this.tstbDelete, "tstbDelete");
            tstbDelete.Click += new System.EventHandler(tstbDelete_Click);


            contextMenuStrip1 = new ContextMenuStrip();
            contextMenuStrip1.Name = "contextMenuStrip1";
            contextMenuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            tstbCopy,
            tstbPaste,
            tstbDelete});
            //resources.ApplyResources(this.contextMenuStrip1, "contextMenuStrip1");

        }
        private void InitDataGridView()
        {
            //dataGridView.ReadOnly = true;
            dataGridView.CurrentCell = null;
            //dataGridView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            //dataGridView.EditMode = DataGridViewEditMode.EditOnEnter;
            dataGridView.MultiSelect = false;
            dataGridView.BackgroundColor = Color.WhiteSmoke;
            dataGridView.RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode.AutoSizeToAllHeaders;
            dataGridView.AllowUserToAddRows = false;

            DataGridViewCheckBoxColumn chkSelect = new DataGridViewCheckBoxColumn();
            chkSelect.Name = COLUMN_NAME_SELECT;
            chkSelect.HeaderText = "SELECT";
            chkSelect.TrueValue = true;
            chkSelect.FalseValue = false;
            chkSelect.DataPropertyName = COLUMN_NAME_SELECT_VALUE;
            dataGridView.Columns.Add(chkSelect);
            dataGridView.Columns[0].Frozen = true;

            DataGridViewTextBoxColumn txtItem = new DataGridViewTextBoxColumn();
            txtItem.Name = COLUMN_NAME_ITEM;
            txtItem.HeaderText = "ITEM";
            dataGridView.Columns.Add(txtItem);
            dataGridView.Columns[1].Frozen = true;

            dataGridView.Columns[0].SortMode = DataGridViewColumnSortMode.NotSortable;
            dataGridView.Columns[0].AutoSizeMode = DataGridViewAutoSizeColumnMode.DisplayedCells;
            dataGridView.Columns[1].SortMode = DataGridViewColumnSortMode.NotSortable;
            dataGridView.Columns[1].AutoSizeMode = DataGridViewAutoSizeColumnMode.DisplayedCells;

            dataGridView.ContextMenuStrip = contextMenuStrip1;


            dataGridView.CellClick += DataGridView_CellClick;       
            dataGridView.CellMouseDown += DataGridView_CellMouseDown;

            dataGridView.CurrentCellDirtyStateChanged += DataGridView_CurrentCellDirtyStateChanged;

        }

        private void DataGridView_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            if (dataGridView.IsCurrentCellDirty)
            {

                bool commitRet= dataGridView.CommitEdit(DataGridViewDataErrorContexts.Commit);
                
                string select = dataGridView.Rows[dataGridView.CurrentRow.Index].Cells[COLUMN_NAME_ITEM].Value.ToString();
                taskItemList[dataGridView.CurrentRow.Index].Item = select;

            }
            //throw new NotImplementedException();
        }

        private void DataGridView_CellMouseDown(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                if (e.RowIndex >= 0)
                {
                    dataGridView.ClearSelection();
                    dataGridView.Rows[e.RowIndex].Selected = true;
                    dataGridView.CurrentCell = dataGridView.Rows[e.RowIndex].Cells[e.ColumnIndex];

                    {
                        propertyGrid.SelectedObject = taskItemList[e.RowIndex].CommonProperties;
                    }
                    selectRowIndex = e.RowIndex;

                    contextMenuStrip1.Show(MousePosition.X, MousePosition.Y);
                }
            }
        }

        private void UpdateCheckBox()
        {
            dataGridView.EndEdit();
            for (int i = 0; i < dataGridView.Rows.Count; i++)
            {
                string select = dataGridView.Rows[i].Cells[COLUMN_NAME_SELECT].Value.ToString();
                taskItemList[i].Enable = bool.Parse(select);
            }
        }

        private void DataGridView_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex == -1)
            {
                return;
            }       

            //if (taskItemList[e.RowIndex].CommonProperties != null)
            {
                propertyGrid.SelectedObject = taskItemList[e.RowIndex].CommonProperties;
            }
        }

        private void FormProperties_Shown(object sender, EventArgs e)
        {
            this.treeView.Enabled = false;

            this.treeView.Nodes.Clear();
            propertyGrid.SelectedObject = null;

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
                this.treeView.Nodes.Add(node);
            }

            this.dataGridView.ClearSelection();

            LoadPlugins();
        }

        private void LoadPlugins()
        {
            string path = "./plugins";
            if (!Directory.Exists(path))
            {
                Directory.CreateDirectory(path);
            }

            string[] filenames = Directory.GetFiles(path, "AILinkFactoryAuto.Plugin.*.dll");
            foreach (var filename in filenames)
            {
                Assembly assembly = Assembly.LoadFrom(filename);
                Type[] types = assembly.GetTypes();
                foreach (Type type in types)
                {
                    if (typeof(IPlugin).IsAssignableFrom(type))
                    {
                        IPlugin plugin = Activator.CreateInstance(type) as IPlugin;
                        plugin.TaskItemList = this.taskItemList;
                        ToolStripItem toolStrip = this.tsmPlugins.DropDownItems.Add(plugin.PluginName);
                        toolStrip.Click += plugin.EventHandler;
                    }
                }

            }
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
                int index = dataGridView.Rows.Add();
                dataGridView.Rows[index].Cells[COLUMN_NAME_SELECT].Value = baseFlowList[i].Enable;
                dataGridView.Rows[index].Cells[COLUMN_NAME_ITEM].Value = baseFlowList[i].Item;
                //dataGridView.Rows[index].Cells[COLUMN_NAME_ITEM].ToolTipText = baseFlowList[i].Tip;
            }
        }
        private void tstbCopy_Click(object sender, EventArgs e)
        {
            selectTaskItem = taskItemList[selectRowIndex];
        }

        private void tstbPaste_Click(object sender, EventArgs e)
        {
            if (selectTaskItem == null)
            {
                MessageBox.Show("请先复制");
                return;
            }
            taskItemList.Insert(selectRowIndex + 1, selectTaskItem);

            dataGridView.Rows.Insert(selectRowIndex + 1, 1);
            dataGridView.Rows[selectRowIndex + 1].Cells[COLUMN_NAME_SELECT].Value = taskItemList[selectRowIndex + 1].Enable;
            dataGridView.Rows[selectRowIndex + 1].Cells[COLUMN_NAME_ITEM].Value = taskItemList[selectRowIndex + 1].Item;

        }

        private void tstbDelete_Click(object sender, EventArgs e)
        {
            taskItemList.RemoveAt(selectRowIndex);
            dataGridView.Rows.RemoveAt(selectRowIndex);
        }

    }
}