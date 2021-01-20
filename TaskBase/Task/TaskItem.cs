using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Task.Executer;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Task
{
    [Serializable]
    public class TaskItem
    {
        private bool enable;

        private string item;

        private CommonProperties commonProperties = new CommonProperties();

        private IExecuter executer;

        public bool Enable
        {
            get { return enable; }
            set { enable = value; }
        }

        public string Item
        {
            get { return item; }
            set { item = value; }
        }

        public CommonProperties CommonProperties
        {
            get
            {
                return commonProperties;
            }

            set
            {
                this.commonProperties = value;
            }
        }

        public IExecuter Executer
        {
            get
            {
                return executer;
            }

            set
            {
                this.executer = value;
            }
        }
    }
}
