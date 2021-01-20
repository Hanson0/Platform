using System.Runtime.InteropServices;
using System.Text;

namespace AILinkFactoryAuto.Common
{
    public class Ini
    {
        [DllImport("kernel32", EntryPoint = "WritePrivateProfileString")]
        public static extern bool WritePrivateProfileString(string lpAppName, string lpKeyName, string lpString, string lpFileName);

        [DllImport("kernel32", EntryPoint = "GetPrivateProfileString")]
        public static extern int GetPrivateProfileString(string lpAppName, string lpKeyName, string lpDefault, StringBuilder lpReturnedString, int nSize, string lpFileName);
    }
}
