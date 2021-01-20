using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace AILinkFactoryAuto.Task.Executer
{
    public class CheckPlusOneRelationExecuter : IExecuter
    {
        private GlobalVaribles configGv;

        private string pattern;
        public CheckPlusOneRelationExecuter()
        {
            this.pattern = GlobalVaribles.PATTERN;
        }

        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            CheckPlusOneRelationProperties config = properties as CheckPlusOneRelationProperties;
            ILog log = globalDic.Get<ILog>();
            configGv = globalDic[typeof(GlobalVaribles).ToString()] as GlobalVaribles;

            string DevWifi_MAC = RemoveMacUnnecessaryChar(PreTranslatCompareInfo(config.DevWifiMac)).ToUpper();
            string DevBt_MAC = RemoveMacUnnecessaryChar(PreTranslatCompareInfo(config.DevBtMac)).ToUpper();

            if (Convert.ToInt64(DevWifi_MAC, 16) + 1 != Convert.ToInt64(DevBt_MAC, 16))
            {
                throw new BaseException(string.Format("WIFI MAC：{0}，BT MAC：{1} 非+1关系，未通过校验 FAIL\r\n", DevWifi_MAC, DevBt_MAC));
            }
            log.Info(string.Format(string.Format("WIFI MAC：{0}，BT MAC：{1} 通过 +1关系校验 PASS\r\n", DevWifi_MAC, DevBt_MAC)));



        }
        private string PreTranslatCompareInfo(string compareInfo)
        {
            string newCheckInfo = compareInfo;
            Match match = Regex.Match(compareInfo, pattern);
            for (int i = 1; i < match.Groups.Count; i++)
            {
                string key = match.Groups[i].ToString();
                newCheckInfo = configGv.Get(key);
            }

            return newCheckInfo;
        }

        private string RemoveMacUnnecessaryChar(string source)
        {
            return source.Replace(":", "").Replace("：", "").Replace(" ","");
        }

    }

}
