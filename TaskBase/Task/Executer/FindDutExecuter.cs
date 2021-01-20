using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.Utils;

namespace AILinkFactoryAuto.Task.Executer
{
    public class FindDutExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            FindDutProperties config = properties as FindDutProperties;
            ILog log = globalDic.Get<ILog>();

            TimeUtils.Execute(() =>
            {
                string dut = HardwareUtils.FindDut(config.DutKeywords);
                if (dut != null)
                {
                    log.Info(string.Format("Find Dut:{0}", dut));
                    return true;
                }

                return false;
            }, config.Timeout);
        }
    }
}
