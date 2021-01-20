using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing.Design;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.View;

namespace AILinkFactoryAuto.Task.Property.Converter
{
    public class DictionaryUiTypeEditor : UITypeEditor
    {

        public override object EditValue(ITypeDescriptorContext context, IServiceProvider provider, object value)
        {
            FormDictionaryEditor formDictionaryEditor = new FormDictionaryEditor(value as IDictionary);
            formDictionaryEditor.ShowDialog();
            return value;
        }

        public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context)
        {
            return UITypeEditorEditStyle.Modal;
        }
    }
}
