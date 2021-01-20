using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;

namespace AILinkFactoryAuto.Task.Executer
{
    public class PrintLabelExecuter : IExecuter
    {
        PrintLabelProperties config;

        string tempalteFolderPath;
        string dataFolderPath;
        ILog log;
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            config = properties as PrintLabelProperties;
            log = globalDic.Get<ILog>();
            GlobalVaribles configGv = globalDic.Get<GlobalVaribles>();

            string content = "";
            string[] split = { ",", "，", " ", "\t" };
            string[] dataHeadList;

            try
            {
                tempalteFolderPath = Path.GetDirectoryName(config.TempalteFile);
                if (!Directory.Exists(tempalteFolderPath))
                {
                    if (!string.IsNullOrEmpty(tempalteFolderPath))
                    {
                        Directory.CreateDirectory(tempalteFolderPath);
                    }
                }

                dataFolderPath = Path.GetDirectoryName(config.DataFile);
                if (!Directory.Exists(dataFolderPath))
                {
                    if (!string.IsNullOrEmpty(dataFolderPath))
                    {
                        Directory.CreateDirectory(dataFolderPath);
                    }
                }
                dataHeadList = config.DataHead.Split(split, StringSplitOptions.RemoveEmptyEntries);
                for (int i = 0; i < dataHeadList.Length; i++)
                {
                    content += configGv.Get(dataHeadList[i]);
                    if (i != dataHeadList.Length - 1)
                    {
                        content += ",";
                    }
                }
            }
            catch (Exception ex)
            {
                throw new Exception(string.Format("标签打印失败,error:内容获取错误,{0}", ex.Message));
            }

            Print(content);
        }


        /// <summary>
        /// 打印
        /// </summary>
        /// <param name="content"></param>
        /// <returns></returns>
        public void Print(string content)
        {
            try
            {
                if (!File.Exists(config.BartenderFile))
                {
                    throw new Exception("BarTender应用程序不存在");

                }

                if (!File.Exists(config.TempalteFile))
                {
                    throw new Exception("BarTender打印模板不存在");
                }

                if (File.Exists(config.DataFile))
                {
                    throw new Exception("存在未打印的打印数据");
                }

                string cmd = GenCmd(config.BartenderFile, config.TempalteFile, config.DataFile);

                log.Info("cmd===" + cmd);

                if (string.IsNullOrEmpty(cmd))
                {
                    throw new Exception("生成打印命名失败"); ;
                }
                log.Info(string.Format("content:{0}", content));

                WriteDataToFile(content);

                ExcecuteCmd(cmd);

                //判断是否打印成功

                Thread.Sleep(config.SleepTimeAfter);
                if (File.Exists(config.DataFile))
                {
                    throw new Exception("打印失败,还存在未打印的打印数据");
                }
            }
            catch (Exception e)
            {
                throw new Exception(string.Format("标签打印失败error:{0}", e.Message));
            }
        }

        /// <summary>
        /// 执行命令
        /// </summary>
        /// <param name="cmd"></param>
        private void ExcecuteCmd(string cmd)
        {
            //执行命令
            Process process = new Process();
            //设置要启动的应用程序
            process.StartInfo.FileName = cmd;
            //是否使用操作系统shell启动
            process.StartInfo.UseShellExecute = false;
            //不显示程序窗口
            process.StartInfo.CreateNoWindow = false;
            process.Start();


            //process.Close();
        }

        /// <summary>
        /// 将打印的内容写入文件
        /// </summary>
        /// <param name="content">打印的内容</param>
        private void WriteDataToFile(string content)
        {
            //往数据文件写入数据
            content = config.DataHead + "\r\n" + content;

            FileInfo fileInfo = new FileInfo(config.DataFile);
            fileInfo.Delete();
            File.WriteAllText(config.DataFile, content, Encoding.Default);
        }

        /// <summary>
        /// 产生打印模板
        /// </summary>
        /// <param name="bartenderFile">BarTender应用程序</param>
        /// <param name="tempalteFile">模板文件</param>
        /// <param name="printType">打印类型</param>
        /// <returns>打印模板</returns>
        private string GenCmd(string bartender, string tempalte, string dataFile)
        {
            return string.Format(GetCmdTemplate(), bartender, tempalte, dataFile);
        }

        /// <summary>
        /// 获取打印命令模板
        /// </summary>
        /// <returns>打印命令模板</returns>
        private string GetCmdTemplate()
        {

            StringBuilder template = new StringBuilder(512);
            string split = " ";
            // 指定barTender.exe路径
            template.Append("\"{0}\"").Append(split).Append("\"");
            // 指定打印标签模板
            template.Append("/AF={1}").Append(split);
            // 指定数据文件
            template.Append("/D={2}").Append(split);
            // 指定起始行
            template.Append("/R=1").Append(split);
            // 指定是否打印
            template.Append("/P\"").Append(split);
            // 不显示界面
            template.Append("\"/NOSPLASH\"").Append(split);
            // 打印完删除文件
            template.Append("\"/DD\"").Append(split);
            // 导致 BarTender 以最小化运行。或者，指定它是在任务栏还是系统任务栏中以最小化的形式出现。
            // /MIN[=Taskbar|SystemTray]
            template.Append("\"/MIN=SystemTray\"").Append(split);
            // 执行完后退出
            //template.Append("\"/X\"");

            return template.ToString();
        }
    }
}
