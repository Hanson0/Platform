using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AILinkFactoryAuto.Task;

namespace AILinkFactoryAuto.Core
{
    public interface IPlugin
    {
        string PluginName { get; }

        List<TaskItem> TaskItemList { set; }

        void EventHandler(object sender, EventArgs e);
    }
}
