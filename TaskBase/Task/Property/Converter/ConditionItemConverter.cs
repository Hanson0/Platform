using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property.Converter
{
    public class ConditionItemConverter : TypeConverter
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
            ConditionItem conditionItem = value as ConditionItem;
            return string.Format("{0},{1},{2}", conditionItem.Key, conditionItem.Condition, conditionItem.Value);
        }

        public override object ConvertFrom(ITypeDescriptorContext context, CultureInfo culture, object value)
        {
            string[] values = value.ToString().Split(new char[] { ',' });
            return new ConditionItem()
            {
                Key = values[0],
                Condition = (Condition) Enum.Parse(typeof(Condition), values[1]),
                Value = values[2]
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
