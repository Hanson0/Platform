using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace AILinkFactoryAuto.Task.Executer
{
    public class CheckMacConsistencyExecuter : IExecuter
    {
        private GlobalVaribles configGv;

        private string pattern;
        public CheckMacConsistencyExecuter()
        {
            this.pattern = GlobalVaribles.PATTERN;
        }

        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            CheckMacConsistencyProperties config = properties as CheckMacConsistencyProperties;
            ILog log = globalDic.Get<ILog>();
            configGv = globalDic[typeof(GlobalVaribles).ToString()] as GlobalVaribles;

            string labelMac = configGv.Get(GlobalVaribles.MAC);
            string deviceMAC = RemoveMacUnnecessaryChar(PreTranslatCompareInfo(config.DeviceMac)).ToUpper();

            if (labelMac != deviceMAC)
            {
                throw new BaseException(string.Format("标签MAC：{0}，产品 MAC：{1} 不一致 \r\n", labelMac, deviceMAC));
            }
            log.Info(string.Format(string.Format("标签MAC：{0}，产品 MAC：{1} 一致\r\n", labelMac, deviceMAC)));



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
            return source.Replace(":", "").Replace("：", "").Replace(" ", "");
        }

    }
}
