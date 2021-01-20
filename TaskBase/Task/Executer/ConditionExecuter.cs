using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Task.Executer
{
    public class ConditionExecuter : IExecuter
    {
        private string pattern;

        private GlobalVaribles configGv;

        public ConditionExecuter()
        {
            this.pattern = GlobalVaribles.PATTERN;
        }

        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            ConditionProperties config = properties as ConditionProperties;
            configGv = globalDic.Get<GlobalVaribles>();
            ILog log = globalDic.Get<ILog>();

            if (config.ConditionItems == null || config.ConditionItems.Length == 0)
            {
                return;
            }

            foreach (var conditionItem in config.ConditionItems)
            {
                Match matchKey = Regex.Match(conditionItem.Key, this.pattern);
                if (!matchKey.Success)
                {
                    throw new BaseException("fail to parse key");
                }

                string key = configGv.Get(matchKey.Groups[1].ToString());
                string value = conditionItem.Value;

                Match matchValue = Regex.Match(conditionItem.Value, this.pattern);
                if (matchValue.Success)
                {
                    value = configGv.Get(matchValue.Groups[1].ToString());
                }

                log.Info("key=" + key);
                log.Info("condition=" + conditionItem.Condition);
                log.Info("value=" + value);

                if (conditionItem.Condition == Condition.EQUAL)
                {
                    if (!key.Equals(value))
                    {
                        throw new BaseException();
                    }
                }

                if (conditionItem.Condition == Condition.GREATER_EQUAL)
                {
                    if (double.Parse(key) >= double.Parse(value))
                    {

                    }
                    else
                    {
                        throw new BaseException();
                    }
                }

                if (conditionItem.Condition == Condition.LESS_EQUAL)
                {
                    if (double.Parse(key) <= double.Parse(value))
                    {

                    }
                    else
                    {
                        throw new BaseException();
                    }
                }
            }
        }
    }
}
