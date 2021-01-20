using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using AILinkFactoryAuto.Utils;

namespace AILinkFactoryAuto.Peripherals
{
    public class Robot
    {
        private static string pathRobot = "./robot\\";
        private string fileSOT = "SOT.ini";
        private string fileEOT = "EOT.ini";
        private string fileBarcode = "Barcode.ini";
        private string fileStates = "States.ini";
        private int interval = 400;

        [DllImport("kernel32", EntryPoint = "GetPrivateProfileString")]
        private static extern int GetPrivateProfileString(
            string lpAppName, string lpKeyName, string lpDefault, StringBuilder lpReturnedString,
            int nSize, string lpFileName);

        [DllImport("kernel32", EntryPoint = "WritePrivateProfileString")]
        private static extern bool WritePrivateProfileString(
            string lpAppName, string lpKeyName, string lpString, string lpFileName);

        private bool enable;

        public bool Enable
        {
            get { return enable; }
            set { enable = value; }
        }

        /// <summary>
        /// 在当前应用程序下，自动创建robot目录，在robot目录下自动创建EOT.ini
        /// </summary>
        public Robot()
        {
            this.enable = true;
            Init();
            CreateEOT();
        }

        private void Init()
        {
            fileSOT = pathRobot + fileSOT;
            fileEOT = pathRobot + fileEOT;
            fileBarcode = pathRobot + fileBarcode;
            fileStates = pathRobot + fileStates;

            if (!Directory.Exists(pathRobot))
            {
                Directory.CreateDirectory(pathRobot);
            }
        }

        /// <summary>
        /// 启动测试
        /// </summary>
        public void Start()
        {
            FindSOT();
            CheckSOTIsDelete();
        }

        private void FindSOT()
        {
            //查找SOT文件
            while (this.enable)
            {
                if (File.Exists(fileSOT))
                {
                    LogUtils.UiInfo.Info(string.Format("file [{0}] is found", fileSOT));
                    //删除EOT文件
                    FileInfo fileInfo = new FileInfo(fileEOT);
                    fileInfo.Delete();
                    LogUtils.UiInfo.Info(string.Format("file [{0}] is deleted", fileEOT));
                    //删除States文件
                    fileInfo = new FileInfo(fileStates);
                    fileInfo.Delete();
                    break;
                }
                LogUtils.UiInfo.Info(string.Format("file [{0}] is not exist", fileSOT));
                Thread.Sleep(interval);
            }
        }

        /// <summary>
        /// 读取SN
        /// </summary>
        /// <returns>机械手扫码枪扫描的标签信息</returns>
        public string GetSn()
        {
            StringBuilder stringBuilder = new StringBuilder(256);
            GetPrivateProfileString("DATA", "MAC", null, stringBuilder, 256, fileBarcode);

            return stringBuilder.ToString();
        }

        private void CheckSOTIsDelete()
        {
            while (this.enable)
            {
                if (!File.Exists(fileSOT))
                {
                    LogUtils.UiInfo.Info(string.Format("file [{0}] was deleted", fileSOT));
                    break;
                }
                else
                {
                    LogUtils.UiInfo.Info(string.Format("file [{0}] is found", fileSOT));
                }

                Thread.Sleep(interval);
            }
        }

        /// <summary>
        /// 结束测试，输出结果
        /// </summary>
        /// <param name="result">测试结果，true：PASS，fail：FAIL</param>
        /// <param name="pass">本次测试之前的PASS数量</param>
        /// <param name="fail">本次测试之前的FAIL数量</param>
        /// <param name="testTime">测试时间</param>
        /// <returns></returns>
        public int CreateStates(bool result, int pass, int fail, string testTime)
        {
            int ret = -1;

            if (result)
            {
                pass += 1;
            }
            else
            {
                fail += 1;
            }

            int total = pass + fail;
            double yield = 0;
            if (total != 0)
            {
                yield = pass / (total * 1.0);
            }

            //[States]
            //COMMAND = UNSELLOAD
            WritePrivateProfileString("States", "COMMAND", "UNSELLOAD", fileStates);
            //TRAY_NUM = 11
            WritePrivateProfileString("States", "TRAY_NUM", "NA", fileStates);
            //LOCAL_X = 11
            WritePrivateProfileString("States", "LOCAL_X", "NA", fileStates);
            //LOCAL_Y = 11
            WritePrivateProfileString("States", "LOCAL_Y", "NA", fileStates);

            //TestResult = Pass
            if (result)
            {
                WritePrivateProfileString("States", "TestResult", "PASS", fileStates);
            }
            else
            {
                WritePrivateProfileString("States", "TestResult", "FAIL", fileStates);
            }

            //TestTime = 3.51
            WritePrivateProfileString("States", "TestTime", testTime, fileStates);
            //ErrorCode = NA
            WritePrivateProfileString("States", "ErrorCode", "NA", fileStates);
            //ErrorMessage = NA
            WritePrivateProfileString("States", "ErrorMessage", "NA", fileStates);
            //YieldRate = 1.00
            WritePrivateProfileString("States", "YieldRate", string.Format("{0:0.00%}", yield).Replace("%", ""), fileStates);
            //YieldPass = 2
            WritePrivateProfileString("States", "YieldPass", pass.ToString(), fileStates);
            //YieldTotal = 2
            WritePrivateProfileString("States", "YieldTotal", total.ToString(), fileStates);
            ret = 0;

            CreateEOT();

            return ret;
        }

        /// <summary>
        /// 结束测试，输出结果
        /// </summary>
        /// <param name="result">测试结果，true：PASS，false：FAIL</param>
        /// <param name="pass">本次测试之前的PASS数量</param>
        /// <param name="fail">本次测试之前的FAIL数量</param>
        /// <param name="testTime">测试时间</param>
        /// <param name="errorCode">错误代码</param>
        /// <param name="errorMessage">错误信息</param>
        /// <returns></returns>
        public int CreateStates(bool result, int pass, int fail, string testTime, string errorCode, string errorMessage)
        {
            int ret = -1;

            if (result)
            {
                pass += 1;
            }
            else
            {
                fail += 1;
            }

            int total = pass + fail;
            double yield = 0;
            if (total != 0)
            {
                yield = pass / (total * 1.0);
            }

            //[States]
            //COMMAND = UNSELLOAD
            WritePrivateProfileString("States", "COMMAND", "UNSELLOAD", fileStates);
            //TRAY_NUM = 11
            WritePrivateProfileString("States", "TRAY_NUM", "NA", fileStates);
            //LOCAL_X = 11
            WritePrivateProfileString("States", "LOCAL_X", "NA", fileStates);
            //LOCAL_Y = 11
            WritePrivateProfileString("States", "LOCAL_Y", "NA", fileStates);

            //TestResult = Pass
            if (result)
            {
                WritePrivateProfileString("States", "TestResult", "PASS", fileStates);
            }
            else
            {
                WritePrivateProfileString("States", "TestResult", "FAIL", fileStates);
            }

            //TestTime = 3.51
            WritePrivateProfileString("States", "TestTime", testTime, fileStates);
            //ErrorCode = NA
            WritePrivateProfileString("States", "ErrorCode", errorCode, fileStates);
            //ErrorMessage = NA
            WritePrivateProfileString("States", "ErrorMessage", errorMessage, fileStates);
            //YieldRate = 1.00
            WritePrivateProfileString("States", "YieldRate", string.Format("{0:0.00%}", yield).Replace("%", ""), fileStates);
            //YieldPass = 2
            WritePrivateProfileString("States", "YieldPass", pass.ToString(), fileStates);
            //YieldTotal = 2
            WritePrivateProfileString("States", "YieldTotal", total.ToString(), fileStates);
            ret = 0;

            CreateEOT();

            return ret;
        }

        private void CreateEOT()
        {

            try
            {
                if (File.Exists(fileEOT))
                {
                    return;
                }

                FileStream fileStream = new FileStream(fileEOT, FileMode.OpenOrCreate);
                fileStream.Dispose();
                fileStream.Close();
            }
            catch (Exception)
            {
                // ignored
            }

            LogUtils.UiInfo.Info(string.Format("create file [{0}]", fileEOT));
        }
    }
}
