using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Task.Executer
{
    public class SleepExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            SleepProperties sleepProperties = properties as SleepProperties;
            Thread.Sleep(sleepProperties.Interval);
        }
    }
}
