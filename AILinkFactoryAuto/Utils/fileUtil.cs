using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Utils
{
    class FileUtil
    {

        public static void fwrite(string folder,string fileName,string message)
        {
            Directory.CreateDirectory(folder);
            string fullFileName = folder + "/" + fileName;
            File.AppendAllText(fullFileName, message + Environment.NewLine);
        }

    }
}
