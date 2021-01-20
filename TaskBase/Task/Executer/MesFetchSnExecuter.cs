using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Task.Property;
using Mes.Test;

namespace AILinkFactoryAuto.Task.Executer
{
    public class MesFetchSnExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            MesFetchSnProperties config = properties as MesFetchSnProperties;
            string mac =  MesProcess.GetMacNoLabel();
            GlobalVaribles configGv = globalDic.Get<GlobalVaribles>();
            configGv.Add(GlobalVaribles.MAC, mac);

            if (config.IsNeedInc1)
            {
                UInt64 macUInt64 = Convert.ToUInt64(mac, 16);
                string macBt = string.Format("{0:X}", macUInt64 + 1).PadLeft(12, '0');
                configGv.Add(GlobalVaribles.MAC_BT, macBt);
            }
        }
    }
}
