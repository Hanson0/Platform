using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;

namespace AILinkFactoryAuto.Task.Property.Converter
{
    public class LimitConverter : TypeConverter
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
            LimitProperties limitProperties = value as LimitProperties;
            return string.Format("{0},{1},{2},{3},{4}", limitProperties.Enable, limitProperties.Name, limitProperties.Lower, limitProperties.Upper, limitProperties.Unit);
        }

        public override object ConvertFrom(ITypeDescriptorContext context, CultureInfo culture, object value)
        {
            string[] values = value.ToString().Split(new char[] { ',' });
            return new LimitProperties()
            {
                Enable = bool.Parse(values[0]),
                Name = values[1],
                Lower = values[2],
                Upper = values[3],
                Unit = values[4],
            };
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
