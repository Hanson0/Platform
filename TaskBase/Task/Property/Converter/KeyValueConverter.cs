using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property.Converter
{
    public class KeyValueConverter : TypeConverter
    {
        public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
        {
            return true;
        }

        public override bool CanConvertFrom(ITypeDescriptorContext context, Type sourceType)
        {
            return true;
        }

        public override object ConvertTo(ITypeDescriptorContext context, CultureInfo culture, object value, Type destinationType)
        {
            KeyValue keyValue = value as KeyValue;
            if (keyValue == null)
            {
                return null;
            }
            return string.Format("{0},{1},{2}", keyValue.Key, keyValue.Value, keyValue.Descripiton);
        }

        public override object ConvertFrom(ITypeDescriptorContext context, CultureInfo culture, object value)
        {
            string[] values = value.ToString().Split(new char[] { ',' });
            KeyValue keyValue = new KeyValue();
            keyValue.Key = values[0];
            keyValue.Value = values[1];
            if (values.Length == 3)
            {
                keyValue.Descripiton = values[2];
            }
            return keyValue;
        }

        public override bool GetPropertiesSupported(ITypeDescriptorContext context)
        {
            return true;
        }

        public override PropertyDescriptorCollection GetProperties(ITypeDescriptorContext context, object value, Attribute[] attributes)
        {
            return TypeDescriptor.GetProperties(value, attributes);
        }
    }
}
