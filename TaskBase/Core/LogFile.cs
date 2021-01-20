using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Core
{
    public class LogFile : ILogFile
    {
        private string fullFileName;

        public LogFile(string fullFileName)
        {
            this.fullFileName = fullFileName;
        }

        public void AppendLine(string line)
        {
            string path = Path.GetDirectoryName(fullFileName);
            Directory.CreateDirectory(path);
            File.AppendAllText(fullFileName, line + Environment.NewLine);
        }
    }
}
