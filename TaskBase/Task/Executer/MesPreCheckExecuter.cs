using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;
using Mes.Test;

namespace AILinkFactoryAuto.Task.Executer
{
    public class MesPreCheckExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            MesPreCheckProperties config = properties as MesPreCheckProperties;
            ILog log = globalDic.Get<ILog>();
            GlobalVaribles configGv = globalDic.Get<GlobalVaribles>();

            if (config.EnableCheckMac)
            {
                string mac = configGv.Get(GlobalVaribles.MAC);
                MesProcess.PreCheck(mac);
                log.Info(string.Format("MAC={0}预检查PASS", mac));
            }

            if (config.EnableCheckImei)
            {
                string imei = configGv.Get(GlobalVaribles.IMEI);
                MesProcess.PreCheck(imei);
                log.Info(string.Format("IMEI={0}预检查PASS", imei));
            }

            if (config.EnableCheckSn)
            {
                string sn = configGv.Get(GlobalVaribles.SN);
                MesProcess.PreCheck(sn);
                log.Info(string.Format("SN={0}预检查PASS", sn));
            }
        }
    }
}
