using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Task;
using AILinkFactoryAuto.Task.Executer;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Utils
{
    /// <summary>
    /// 框架默认TaskItem管理，生成.jts测试序列
    /// </summary>
    public class TaskItemManager
    {
        private List<TaskItem> taskItemList;

        private TaskItem taskItemInit;

        private TaskItem taskItemParseLabel;

        private TaskItem taskItemDeinit;

        private TaskItem taskItemMesPreCheck;

        private TaskItem taskItemPrintLabel;

        private InitProperties initProperties;

        private ParseLabelProperties parseLabelProperties;

        private MesPreCheckProperties mesPreCheckProperties;
        
        private PrintLabelProperties printLabelProperties;

        private DeinitProperties deinitProperties;

        /// <summary>
        /// TaskItemInit
        /// </summary>
        public TaskItem TaskItemInit
        {
            get { return taskItemInit; }
        }

        /// <summary>
        /// TaskTtemParseLabel
        /// </summary>
        public TaskItem TaskItemParseLabel
        {
            get { return taskItemParseLabel; }
        }

        /// <summary>
        /// TaskItemMesPreCheck
        /// </summary>
        public TaskItem TaskItemMesPreCheck
        {
            get { return taskItemMesPreCheck; }
        }

        /// <summary>
        /// TaskItemDeinit
        /// </summary>
        public TaskItem TaskItemDeinit
        {
            get { return taskItemDeinit; }
        }

        /// <summary>
        /// 
        /// </summary>
        public TaskItem TaskItemPrintLabel
        {
            get { return taskItemPrintLabel; }
        }

        /// <summary>
        /// InitProperties
        /// </summary>
        public InitProperties InitProperties
        {
            get { return initProperties; }
        }

        /// <summary>
        /// ParseLabelProperties
        /// </summary>
        public ParseLabelProperties ParseLabelProperties
        {
            get { return parseLabelProperties; }
        }

        /// <summary>
        /// MesPreCheckProperties
        /// </summary>
        public MesPreCheckProperties MesPreCheckProperties
        {
            get { return mesPreCheckProperties; }
        }
        /// <summary>
        /// 
        /// </summary>
        public PrintLabelProperties PrintLabelProperties
        {
            get { return printLabelProperties; }
        }

        /// <summary>
        /// DeinitProperties
        /// </summary>
        public DeinitProperties DeinitProperties
        {
            get { return deinitProperties; }
        }

        /// <summary>
        /// 添加TaskItem
        /// </summary>
        /// <param name="taskItem">TaskItem</param>
        public void Put(TaskItem taskItem)
        {
            taskItemList.Add(taskItem);
        }

        /// <summary>
        /// 添加TaskItem
        /// </summary>
        /// <param name="taskItem">TaskItem</param>
        public void Append(TaskItem taskItem)
        {
            taskItemList.Add(taskItem);
        }

        /// <summary>
        /// 新增iMES预检查
        /// </summary>
        /// <param name="properties">MesPreCheckProperties</param>
        public void AppendNewMesPreCheck(MesPreCheckProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "iMES Pre Check";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new MesPreCheckExecuter();
            Append(taskItem);
        }

        public void AppendScanBarcode(ScanCodeProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "Scan Code";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new ScanCodeExecuter();
            Append(taskItem);
        }

        public void AppendUserConfirm(UserConfirmProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "用户判断";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new UserConfirmExecuter();
            Append(taskItem);
        }

        public void AppendMesFetchSn(MesFetchSnProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "MES Fetch Sn";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new MesFetchSnExecuter();
            Append(taskItem);
        }

        /// <summary>
        /// 标签打印功能
        /// </summary>
        public void AppendPrintLabel(PrintLabelProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "Print Label";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new PrintLabelExecuter();
            Append(taskItem);
        }

        public void AppendReadNetCardMac(ReadMacNetCardProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "Read Mac NetCard";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new ReadMacNetCardExecuter();
            Append(taskItem);
        }

        public void AppendCheckMaterialInfo(CheckMaterialInfoProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "Check Material Info";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new CheckMaterialInfoExecuter();
            Append(taskItem);
        }

        public void AppendFindDut(FindDutProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "Find Dut";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new FindDutExecuter();
            Append(taskItem);
        }
        public void AppendCheckPlusOneRelation(CheckPlusOneRelationProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "Check PlusOne Relation";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new CheckPlusOneRelationExecuter();
            Append(taskItem);
        }

        public void AppendCheckMacConsistency(CheckMacConsistencyProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "Check Mac Consistency";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new CheckMacConsistencyExecuter();
            Append(taskItem);
        }

        public void AppendSync(SyncProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "Sync";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new SyncExecuter();
            Append(taskItem);
        }

        /// <summary>
        /// 生成测试序列
        /// </summary>
        /// <returns>List<TaskItem></returns>
        public List<TaskItem> Generate()
        {
            End();
            return taskItemList;
        }

        public void Save2Jts(IGenJts genJts, uint dutSeq, string name)
        {
            Generate();
            StringBuilder filename = new StringBuilder();
            filename.Append(genJts.ProjectPath);
            filename.Append("\\DUT" + dutSeq);
            filename.Append("_");
            filename.Append(name);
            filename.Append(".jts");
            JtsUtils.SaveJsonFile(filename.ToString(), taskItemList);
        }

        /// <summary>
        /// 实例化
        /// </summary>
        /// <param name="properties">ParseLabelProperties</param>
        public TaskItemManager(ParseLabelProperties properties)
        {
            parseLabelProperties = properties;

            Init();
        }

        /// <summary>
        /// 实例化
        /// </summary>
        public TaskItemManager()
        {
            taskItemList = new List<TaskItem>();
            taskItemInit = new TaskItem();
            taskItemDeinit = new TaskItem();

            initProperties = new InitProperties()
            {
                TopMost = false,
                ExecuteCondition = ExecuteCondition.ALWAYS
            };
            deinitProperties = new DeinitProperties()
            {
                TopMost = false,
                ExecuteCondition = ExecuteCondition.ALWAYS
            };

            taskItemInit.Enable = true;
            taskItemInit.Item = "Init";
            taskItemInit.CommonProperties = initProperties;
            taskItemInit.Executer = new InitExecuter();
            Append(taskItemInit);
        }

        public void AppendParseLabel(ParseLabelProperties properties)
        {
            TaskItem taskItem = new TaskItem();
            taskItem.Enable = true;
            taskItem.Item = "扫码枪扫描标签";
            taskItem.CommonProperties = properties;
            taskItem.Executer = new ParseLabelExecuter();
            Append(taskItem);
        }

        /// <summary>
        /// 初始化
        /// </summary>
        private void Init()
        {
            taskItemList = new List<TaskItem>();
            taskItemInit = new TaskItem();
            taskItemParseLabel = new TaskItem();
            taskItemDeinit = new TaskItem();
            taskItemMesPreCheck = new TaskItem();
            //ADD BY ZengJiahao
            taskItemPrintLabel = new TaskItem();

            initProperties = new InitProperties()
            {
                TopMost = false,
                ExecuteCondition = ExecuteCondition.ALWAYS
            };
            mesPreCheckProperties = new MesPreCheckProperties();
            deinitProperties = new DeinitProperties()
            {
                TopMost = false,
                ExecuteCondition = ExecuteCondition.ALWAYS
            };
            Start();
        }

        /// <summary>
        /// 添加框架前置TaskItem，Init, Parse Label，iMES Pre Check
        /// </summary>
        private void Start()
        {
            taskItemInit.Enable = true;
            taskItemInit.Item = "Init";
            taskItemInit.CommonProperties = initProperties;
            taskItemInit.Executer = new InitExecuter();
            Put(taskItemInit);

            taskItemParseLabel.Enable = true;
            taskItemParseLabel.Item = "扫码枪扫描标签";
            taskItemParseLabel.CommonProperties = parseLabelProperties;
            taskItemParseLabel.Executer = new ParseLabelExecuter();
            Put(taskItemParseLabel);

            //taskItemMesPreCheck.Enable = false;
            //taskItemMesPreCheck.Item = "iMES Pre Check";
            //taskItemMesPreCheck.CommonProperties = mesPreCheckProperties;
            //taskItemMesPreCheck.Executer = new MesPreCheckExecuter();
            //Put(taskItemMesPreCheck);
        }

        /// <summary>
        /// 添加Deinit
        /// </summary>
        private void End()
        {

            taskItemDeinit.Enable = true;
            taskItemDeinit.Item = "Deinit";
            taskItemDeinit.CommonProperties = deinitProperties;
            taskItemDeinit.Executer = new DeinitExecuter();
            Put(taskItemDeinit);
        }
    }
}
