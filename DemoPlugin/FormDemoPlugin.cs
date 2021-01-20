using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task;

namespace AILinkFactoryAuto.Plugin
{
    public partial class FormDemoPlugin : Form, IPlugin
    {
        private List<TaskItem> taskItemList;

        public FormDemoPlugin()
        {
            InitializeComponent();
        }

        public string PluginName
        {
            get
            {
                return "DemoPlugin";
            }
        }

        public List<TaskItem> TaskItemList
        {
            set
            {
                this.taskItemList = value;
            }
        }

        public void EventHandler(object sender, EventArgs e)
        {
            this.ShowDialog();
        }

        private void FormDemoPlugin_Load(object sender, EventArgs e)
        {
        }
    }
}
