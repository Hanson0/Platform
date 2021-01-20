using AILinkFactoryAuto.Task.Property.Converter;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    [TypeConverter(typeof(KeyValueConverter))]
    public class KeyValue
    {
        private string key;

        private string value;

        private string descripiton;

        [Category("Common"), Description("key")]
        public string Key
        {
            get { return key; }
            set { key = value; }
        }

        [Category("Common"), Description("value")]
        public string Value
        {
            get { return value; }
            set { this.value = value; }
        }

        [Category("Common"), Description("description")]
        public string Descripiton
        {
            get { return descripiton; }
            set { descripiton = value; }
        }

        //public override string ToString()
        //{
        //    return string.Format("[key={0},value={1}]");
        //}

        //public override bool Equals(object obj)
        //{
        //    if (obj == null)
        //    {
        //        return false;
        //    }

        //    if (typeof(string) != obj.GetType())
        //    {
        //        return false;
        //    }

        //    if (this.key != (string)obj)
        //    {
        //        return false;
        //    }

        //    return true;
        //}

        //public override int GetHashCode()
        //{
        //    if (key == null)
        //    {
        //        return 0;
        //    }

        //    return this.key.GetHashCode();
        //}
    }
}
