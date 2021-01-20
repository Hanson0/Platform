using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class ExeProperties : CommonProperties
    {
        private string fileName;

        private string[] arguments;

        private string[] checkArray;

        private string path;

        private bool singleton;

        [Category("Common"), Description("file name")]
        public string FileName
        {
            get { return fileName; }
            set { fileName = value; }
        }

        [Category("Common"), Description("arguments")]
        public string[] Arguments
        {
            get { return arguments; }
            set { arguments = value; }
        }

        [Category("Common"), Description("check list")]
        public string[] CheckArray
        {
            get { return checkArray; }
            set { checkArray = value; }
        }

        [Category("Common"), Description("path")]
        public string Path
        {
            get { return path; }
            set { path = value; }
        }

        [Category("Common"), Description("singleton")]
        public bool Singleton
        {
            get { return singleton; }
            set { singleton = value; }
        }
    }
}
