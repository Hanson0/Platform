using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace AILinkFactoryAuto.Task
{
    public class GlobalVaribles
    {
        public static string PATTERN = @"^{([0-9a-zA-Z_]+)}$";

        private Dictionary<string, object> keyValue = new Dictionary<string, object>();

        private Form form;

        public static string LABEL_SN = "LABEL_SN";
        public static string IMEI = "IMEI";
        public static string SN = "SN";
        public static string MEID = "MEID";
        public static string MAC = "MAC";
        public static string ICCID = "ICCID";
        public static string IMSI = "IMSI";
        public static string EID = "EID";
        public static string NFC = "NFC";
        public static string SSID = "SSID";
        public static string TBSN = "TBSN";
        public static string POWERSN = "POWERSN";
        public static string MAC_BT = "MAC_BT";

        public void Add(string key, string value)
        {
            if (keyValue.ContainsKey(key))
            {
                keyValue.Remove(key);
            }
            keyValue.Add(key, value);
        }

        public void Add(string key, object value)
        {
            if (keyValue.ContainsKey(key))
            {
                keyValue.Remove(key);
            }
            keyValue.Add(key, value);
        }

        public string Get(string key)
        {
            if (keyValue.ContainsKey(key))
            {
                return keyValue[key].ToString();
            }

            return null;
        }

        public object GetObject(string key)
        {
            if (keyValue.ContainsKey(key))
            {
                return keyValue[key];
            }

            return null;
        }

        public Form Form
        {
            get { return form; }
            set { form = value; }
        }
    }
}
