using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Task.Property.Converter;

namespace AILinkFactoryAuto.Task.Property
{
    [TypeConverter(typeof(LimitConverter))]
    public class LimitProperties
    {
        private bool enable = true;

        private string name;

        private string lower;

        private string upper;

        private string unit;

        [Description("enable")]
        public bool Enable
        {
            get { return enable; }
            set { enable = value; }
        }

        [Description("lower")]
        public string Lower
        {
            get { return lower; }
            set { lower = value; }
        }

        [Description("upper")]
        public string Upper
        {
            get { return upper; }
            set { upper = value; }
        }

        [Description("unit")]
        public string Unit
        {
            get { return unit; }
            set { unit = value; }
        }

        [Description("name")]
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
    }
}
