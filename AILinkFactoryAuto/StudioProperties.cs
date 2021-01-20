using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using AILinkFactoryAuto.Common;

namespace AILinkFactoryAuto
{
    class StudioProperties
    {
        private static string defaultFileName = "SetUp.ini";
        private static string defaultFullFileName;
        private static int defaultCapacityOfStringbuilder = 256;

        static StudioProperties()
        {
            defaultFullFileName = Path.Combine(Environment.CurrentDirectory, defaultFileName);
        }

        private static bool autoStart;

        public static bool AutoStart
        {
            get
            {
                StringBuilder stringBuilder = new StringBuilder(defaultCapacityOfStringbuilder);
                Ini.GetPrivateProfileString("Studio", "AutoStart", "", stringBuilder, defaultCapacityOfStringbuilder, defaultFullFileName);
                if ("1" == stringBuilder.ToString())
                {
                    return true;
                }
                return false;
            }
            set
            {
                string _value;
                if (value)
                {
                    _value = "1";
                }
                else
                {
                    _value = "0";
                }
                Ini.WritePrivateProfileString("Studio", "AutoStart", _value, defaultFullFileName);
            }
        }

        private static bool enableRobot;

        public static bool EnableRobot
        {
            get
            {
                StringBuilder stringBuilder = new StringBuilder(defaultCapacityOfStringbuilder);
                Ini.GetPrivateProfileString("Studio", "EnableRobot", "", stringBuilder, defaultCapacityOfStringbuilder, defaultFullFileName);
                if ("1" == stringBuilder.ToString())
                {
                    return true;
                }
                return false;
            }
            set
            {
                string _value;
                if (value)
                {
                    _value = "1";
                }
                else
                {
                    _value = "0";
                }
                Ini.WritePrivateProfileString("Studio", "EnableRobot", _value, defaultFullFileName);
            }
        }

        public static string RememberUserName
        {
            get
            {
                StringBuilder stringBuilder = new StringBuilder(defaultCapacityOfStringbuilder);
                Ini.GetPrivateProfileString("UserName", "Remember", "", stringBuilder, 256, defaultFullFileName);
                return stringBuilder.ToString();
            }
            set
            {

                Ini.WritePrivateProfileString("UserName", "Remember", value, defaultFullFileName);
            }
        }

        public static string BaseUrl
        {
            get
            {
                StringBuilder stringBuilder = new StringBuilder(defaultCapacityOfStringbuilder);
                Ini.GetPrivateProfileString("Server", "baseurl", "", stringBuilder, 256, defaultFullFileName);
                return stringBuilder.ToString();
            }
            set
            {
                Ini.WritePrivateProfileString("Server", "baseurl", value, defaultFullFileName);
            }

        }
        public static string UrlUploadModifyJts
        {
            get
            {
                StringBuilder stringBuilder = new StringBuilder(defaultCapacityOfStringbuilder);
                Ini.GetPrivateProfileString("Server", "url_uploadModifyJts", "", stringBuilder, 256, defaultFullFileName);
                return BaseUrl + stringBuilder.ToString();
            }
            set
            {
                Ini.WritePrivateProfileString("Server", "url_uploadModifyJts", value, defaultFullFileName);
            }
        }
    }
}
