using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.Utils;

namespace AILinkFactoryAuto.Task.Executer
{
    public class ExeExecuter : IExecuter
    {
        private static bool isRunning;
        private static string responseGlobal;
        private static object lockObject = new object();

        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            ExeProperties config = properties as ExeProperties;
            ILog log = globalDic.Get<ILog>();

            string response = null;
            if (config.Singleton)
            {
                bool isFirst = false;
                lock (lockObject)
                {     
                    if (!isRunning)
                    {
                        isFirst = true;
                        isRunning = true;
                    }                
                }

                if (isFirst)
                {
                    try
                    {
                        responseGlobal = ExecuteExe(config, log);
                    }
                    catch (Exception e)
                    {
                        throw e;
                    }
                    finally
                    {
                        isRunning = false;
                    }
                }

                if (isRunning)
                {
                    TimeUtils.Execute(() =>
                    {
                        return !isRunning;
                    }, config.Timeout);
                }
                response = responseGlobal;
            }
            else
            {
                response = ExecuteExe(config, log);
            }
            
            log.Info(response);
            if (config.CheckArray != null)
            {
                bool result = true;
                string error = null;
                foreach (var check in config.CheckArray)
                {
                    log.Info("check:" + check);
                    if (!response.Contains(check))
                    {
                        error = check;
                        result = false;
                        break;
                    }
                }

                if (!result)
                {
                    throw new BaseException("not contain " + error);
                }
            }

        }

        private string ExecuteExe(ExeProperties config, ILog log)
        {
            string response = null;
            string path = Path.Combine(Environment.CurrentDirectory, config.Path);
            string filename = Path.Combine(path, config.FileName);
            log.Info("bat:" + File.ReadAllText(filename));
            string filenameResult = string.Format("{0}.txt", Thread.CurrentThread.ManagedThreadId);
            Process process = new Process();
            try
            {
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.RedirectStandardError = false;
                process.StartInfo.RedirectStandardInput = false;
                process.StartInfo.RedirectStandardOutput = false;
                process.StartInfo.CreateNoWindow = true;
                process.StartInfo.FileName = filename;
                string workingDirectory = path;
                StringBuilder arguments = new StringBuilder();
                arguments.Append(filenameResult);
                foreach (var argument in config.Arguments)
                {
                    arguments.Append(" ");
                    arguments.Append(argument);
                }
                process.StartInfo.Arguments = arguments.ToString();
                log.Info("arguments:" + arguments);
                process.StartInfo.WorkingDirectory = workingDirectory;
                process.Start();

                if (process.WaitForExit(config.Timeout))
                {
                    response += File.ReadAllText(Path.Combine(path, filenameResult));
                }
            }
            catch (Exception e)
            {
                throw e;
            }
            finally
            {
                FileInfo fileInfo = new FileInfo(Path.Combine(path, filenameResult));
                fileInfo.Delete();
                if (!process.HasExited)
                {
                    process.Kill();
                }
            }


            return response;
        }
    }
}
