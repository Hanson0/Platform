using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.Utils;

namespace AILinkFactoryAuto.Task.Executer
{
    public class SyncExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            SyncProperties config = properties as SyncProperties;
            CountLatch sync = globalDic.Get<CountLatch>();

            sync.CountDown(config.Key);

            TimeUtils.Execute(() =>
            {
                if (sync.GetCount(config.Key) == 0)
                {
                    return true;
                }

                return false;
            }, config.Timeout);
        }
    }
}
