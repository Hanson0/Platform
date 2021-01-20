using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Dut.AtCommand.Property;
using AILinkFactoryAuto.Task;
using AILinkFactoryAuto.Task.Executer;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.Utils;

namespace AILinkFactoryAuto.Dut.AtCommand.Executer
{
    public class OpenPhoneExecutor : IExecuter
    {
        //多线程时应该加互斥锁
        public static List<ComDut> comDutList = new List<ComDut>();
        public static List<OpenPhoneProperties> configList = new List<OpenPhoneProperties>();
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            OpenPhoneProperties config = properties as OpenPhoneProperties;
            ILog log = globalDic[typeof(ILog).ToString()] as ILog;

            string com = null;
            //if (config.AtType == AtType.Auto_Qualcomm_Application)
            //{
            //    TimeUtils.Execute(() =>
            //    {
            //        com = HardwareUtils.GetCom("Device Application Interface");
            //        if (!string.IsNullOrEmpty(com))
            //        {
            //            log.Info(string.Format("Device Application Interface ({0})", com));
            //            return true;
            //        }
            //        return false;
            //    }, config.Timeout);
            //}

            //if (config.AtType == AtType.Auto_Huawei_Application)
            //{
            //    TimeUtils.Execute(() =>
            //    {
            //        com = HardwareUtils.GetCom("HUAWEI Mobile Connect - PC UI Interface");
            //        if (!string.IsNullOrEmpty(com))
            //        {
            //            log.Info(string.Format("HUAWEI Mobile Connect - PC UI Interface ({0})", com));
            //            return true;
            //        }

            //        com = HardwareUtils.GetCom("HUAWEI Mobile Connect - 3G PC UI Interface");
            //        if (!string.IsNullOrEmpty(com))
            //        {
            //            log.Info(string.Format("HUAWEI Mobile Connect - 3G PC UI Interface ({0})", com));
            //            return true;
            //        }
            //        return false;
            //    }, config.Timeout);
            //}

            if (config.AtType == AtType.Auto)
            {
                TimeUtils.Execute(() =>
                {
                    foreach (var key in config.AutoKey)
                    {
                        com = HardwareUtils.GetCom(key);
                        if (!string.IsNullOrEmpty(com))
                        {
                            log.Info(string.Format("{0} ({1})", key, com));
                            return true;
                        }
                    }
                    return false;
                }, config.Timeout);
            }

            Thread.Sleep(config.SleepTimeAfterFindDut);

            ComDut comDut = new ComDut();
            if(config.AtType == AtType.Manual)
            {
                comDut.PortName = config.PortName;
            }
            else
            {
                comDut.PortName = com;
            }
            comDut.BaudRate = config.BaudRate;
            comDut.DataBits = 8;
            comDut.StopBits = StopBits.One;
            comDut.Parity = config.Parity;

            //comDut.RtsEnable = config.Rts;
            //comDut.DtrEnable = config.Dtr;

            TimeUtils.Execute(() =>
            {
                try
                {
                    comDut.Close();
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                }

                try
                {
                    comDut.Open();
                    return true;
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                    return false;
                }
            }, config.Timeout);

            comDutList.Add(comDut);
            if (globalDic.ContainsKey(typeof(List<ComDut>).ToString()))
            {
                globalDic[typeof(List<ComDut>).ToString()] = comDutList;
            }
            else
            {
                globalDic.Add(typeof(List<ComDut>).ToString(), comDutList);
            }



            configList.Add(config);
            if (globalDic.ContainsKey(typeof(List<OpenPhoneProperties>).ToString()))
            {
                globalDic[typeof(List<OpenPhoneProperties>).ToString()] = configList;
            }
            else
            {
                globalDic.Add(typeof(List<OpenPhoneProperties>).ToString(), configList);
            }

        }
    }
}
