using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.Utils;

namespace AILinkFactoryAuto.Task.Executer
{
    public class InitExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            LogUtils.UiDebug.Info("Start Init......");
            InitProperties config = properties as InitProperties;
            GlobalVaribles configGlobal = globalDic[typeof(GlobalVaribles).ToString()] as GlobalVaribles;
            configGlobal.Form.Invoke((EventHandler) delegate
            {
                configGlobal.Form.TopMost = config.TopMost;
            });
        }
    }
}
