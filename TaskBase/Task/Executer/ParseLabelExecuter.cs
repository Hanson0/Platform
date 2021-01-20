using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Task.Executer
{
    public class ParseLabelExecuter : IExecuter
    {      
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            ParseLabelProperties config = properties as ParseLabelProperties;
            GlobalVaribles configGv = globalDic[typeof(GlobalVaribles).ToString()] as GlobalVaribles;
            ILog log = globalDic[typeof(ILog).ToString()] as ILog;

            string[] data = configGv.Get(GlobalVaribles.LABEL_SN).Split(new[] {','});

            if (config.ImeiLocation > 0 && config.ImeiLocation <= data.Length)
            {
                configGv.Add(GlobalVaribles.IMEI, data[config.ImeiLocation - 1]);
            }

            if (config.SnLocation > 0 && config.SnLocation <= data.Length)
            {
                configGv.Add(GlobalVaribles.SN, data[config.SnLocation - 1]);
            }

            if (config.MeidLocation > 0 && config.MeidLocation <= data.Length)
            {
                configGv.Add(GlobalVaribles.MEID, data[config.MeidLocation - 1]);
            }

            if (config.MacLocation > 0 && config.MacLocation <= data.Length)
            {
                configGv.Add(GlobalVaribles.MAC, data[config.MacLocation - 1]);
            }

            log.Info(string.Format("IMEI={0}", configGv.Get(GlobalVaribles.IMEI)));
            log.Info(string.Format("MEID={0}", configGv.Get(GlobalVaribles.MEID)));
            log.Info(string.Format("SN={0}", configGv.Get(GlobalVaribles.SN)));
            log.Info(string.Format("MAC={0}", configGv.Get(GlobalVaribles.MAC)));

            //867404030012435,AL1710300110002
            if (config.ImeiLocation > 0)
            {
                CheckImei(configGv.Get(GlobalVaribles.IMEI));
            }

            if (config.MeidLocation > 0)
            {
                // TODO
            }

            if (config.SnLocation > 0)
            {
                CheckSn(configGv.Get(GlobalVaribles.SN));
            }

            if (config.MacLocation > 0)
            {
                CheckMac(configGv.Get(GlobalVaribles.MAC));
            }
        }

        private void CheckMac(string mac)
        {
            string format = "^[0-9A-Z]{12}$";

            if (string.IsNullOrEmpty(mac))
            {
                throw new BaseException("MAC null");
            }

            if (!Regex.IsMatch(mac, format))
            {
                throw new BaseException("MAC invalid");
            }
        }

        private void CheckSn(string sn)
        {
            string format = "^[0-9A-Z]{15}$";

            if (string.IsNullOrEmpty(sn))
            {
                throw new BaseException("SN null");
            }

            if (!Regex.IsMatch(sn, format))
            {
                throw new BaseException("SN invalid");
            }
        }

        private void CheckImei(string imei)
        {
            string format = "^[0-9]{15}$";

            if (string.IsNullOrEmpty(imei))
            {
                throw new BaseException("IMEI null");
            }

            if (!Regex.IsMatch(imei, format))
            {
                throw new BaseException("IMEI invalid");
            }
        }
    }
}
