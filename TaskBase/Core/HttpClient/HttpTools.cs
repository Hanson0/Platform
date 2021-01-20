using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using AILinkFactoryAuto.Utils;

namespace AILinkFactoryAuto.Core.HttpClient
{
    public class HttpTools
    {
        public static void Download(string url, string fullFileName)
        {

            string directory = Path.GetDirectoryName(fullFileName);
            if (!string.IsNullOrEmpty(directory) && !Directory.Exists(directory))
            {
                Directory.CreateDirectory(directory);
            }
            HttpWebRequest request = WebRequest.Create(url) as HttpWebRequest;
            HttpWebResponse response = request.GetResponse() as HttpWebResponse;
            Stream responseStream = response.GetResponseStream();
            Stream stream;
            stream = new FileStream(fullFileName, FileMode.Create);

            byte[] bArr = new byte[1024];
            int size = responseStream.Read(bArr, 0, (int)bArr.Length);
            while (size > 0)
            {
                stream.Write(bArr, 0, size);
                size = responseStream.Read(bArr, 0, (int)bArr.Length);
            }
            stream.Close();
            responseStream.Close();
            LogUtils.UiDebug.Debug("Download-->url==" + url + "fullFileName==" + fullFileName);
        }

        public static string GetFilenameFromUrl(string url)
        {
            Uri uri = new Uri(url);
            return uri.Segments[uri.Segments.Length - 1];
        }
    }
}
