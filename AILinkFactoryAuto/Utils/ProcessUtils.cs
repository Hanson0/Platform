using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Utils
{
    class ProcessUtils
    {
        public static string GetAppPath()
        {
            string filename = Process.GetCurrentProcess().MainModule.FileName;
            return Path.GetDirectoryName(filename);
        }
    }
}
