using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class CheckMaterialInfoProperties : CommonProperties
    {
        private string materialCode;

        private string materialModel;

        [Category("Common"), Description("material code")]
        public string MaterialCode
        {
            get { return materialCode; }
            set { materialCode = value; }
        }

        [Category("Common"), Description("material model")]
        public string MaterialModel
        {
            get { return materialModel; }
            set { materialModel = value; }
        }
    }
}
