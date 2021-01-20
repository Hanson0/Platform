using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WeifenLuo.WinFormsUI.Docking;

namespace AILinkFactoryAuto.Utils
{
    class DockPanelUtils
    {
        private static DockPanel _dockPanel;

        public static void SetDockPanel(DockPanel dockPanel)
        {
            _dockPanel = dockPanel;
        }

        public static DockPanel GetDockPanel()
        {
            return _dockPanel;
        }
    }
}
