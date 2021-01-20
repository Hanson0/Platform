using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Task.Property.Converter;

namespace AILinkFactoryAuto.Task.Property
{
    public enum Condition
    {
        EQUAL,
        GREATER_EQUAL,
        LESS_EQUAL
    }

    [TypeConverter(typeof(ConditionItemConverter))]
    public class ConditionItem
    {
        private Condition condition;

        private string key;

        private string value;

        [Description("conditon")]
        public Condition Condition
        {
            get { return condition; }
            set { condition = value; }
        }

        [Description("key")]
        public string Key
        {
            get { return key; }
            set { key = value; }
        }

        [Description("value")]
        public string Value
        {
            get { return value; }
            set { this.value = value; }
        }
    }

    public class ConditionProperties : CommonProperties
    {
        private ConditionItem[] conditionItems;

        [Category("Common"), Description("condtion item list")]
        public ConditionItem[] ConditionItems
        {
            get { return conditionItems; }
            set { conditionItems = value; }
        }
    }
}
