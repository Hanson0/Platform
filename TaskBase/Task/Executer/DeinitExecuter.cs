using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Task.Executer
{
    public class DeinitExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            DeinitProperties config = properties as DeinitProperties;
            GlobalVaribles configGlobal = globalDic[typeof(GlobalVaribles).ToString()] as GlobalVaribles;
            configGlobal.Form.Invoke((EventHandler)delegate
            {
                configGlobal.Form.TopMost = config.TopMost;
            });

            globalDic.Put(config);
        }
    }
}
