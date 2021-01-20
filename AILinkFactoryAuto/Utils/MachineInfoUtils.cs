using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using System.Threading.Tasks;

using System.Net;

using System.Management;  //在项目-》添加引用....里面引用System.Management

using System.Runtime.InteropServices;

namespace AILinkFactoryAuto.Utils
{

    //此类用于获取当前主机的相关信息
    public class MachineInfoUtils
    {


        public string GetHostName()
        {
            try
            {
                return Dns.GetHostName();
            }
            catch (Exception)
            {
                
                throw;
            }
        }


        //public string example()
        //{

        //    //string Info = "";

        //    MachineInfoUtils info = MachineInfoUtils.I();       //获取主机的对象信息

        //    Info = "\r\n主机名:" + Dns.GetHostName(); //获取主机名称

        //    Info += "\r\n系统类型:" + info.GetSystemType();

        //    Info += "\r\n物理内存:" + info.GetPhysicalMemory();

        //    Info += "\r\n\r\n本地IP:";

        //    string[] LocalIp = info.GetLocalIpAddress();

        //    foreach (string ip in LocalIp) Info += "\r\n" + ip;

        //    //Info += "\r\n\r\n外网IP:";

        //    //string[] ExternalIp = info.GetExtenalIpAddress();

        //    //foreach (string ip in ExternalIp) Info += "\r\n" + ip;
        //    Info += "\r\n\r\nMAC:";

        //    Info += "\r\n" + info.GetNetCardMACAddress();

        //    //Info += "\r\n" + info.GetMacAddress(LocalIp[0]); 
        //    Info += "\r\n";

        //    cpuNum = info.GetCPUSerialNumber();
        //    Info += "\r\nCPU序列号:" + cpuNum;
        //    //Info += "\r\nCPU编号:" + info.GetCPUID();

        //    //Info += "\r\nCPU版本信息:" + info.GetCPUVersion();

        //    //Info += "\r\nCPU名称信息:" + info.GetCPUName();

        //    //Info += "\r\nCPU制造厂商:" + info.GetCPUManufacturer();

        //    //Info += "\r\n主板制造厂商:" + info.GetBoardManufacturer();

        //    //Info += "\r\n主板序列号:" + info.GetBIOSSerialNumber();

        //    //Info += "\r\n硬盘序列号:" + info.GetHardDiskSerialNumber();

        //    //Info += "\r\n显卡PNPDeviceID:\r\n" + info.GetVideoPNPID();

        //    //Info += "\r\n声卡PNPDeviceID:\r\n" + info.GetSoundPNPID();

        //    return Info;

        //}









        static MachineInfoUtils Instance;





        /// <summary>

        /// 获取当前类对象的一个实例

        /// </summary>

        public static MachineInfoUtils I()
        {

            if (Instance == null) Instance = new MachineInfoUtils();

            return Instance;

        }



        /// <summary>

        /// 获取本地ip地址，多个ip

        /// </summary>

        public String[] GetLocalIpAddress()
        {

            string hostName = Dns.GetHostName();                    //获取主机名称

            IPAddress[] addresses = Dns.GetHostAddresses(hostName); //解析主机IP地址
            string[] IP = new string[addresses.Length];             //转换为字符串形式

            for (int i = 0; i < addresses.Length; i++) IP[i] = addresses[i].ToString();
            return IP;

        }

        //从网站"http://1111.ip138.com/ic.asp"，获取本机外网ip地址信息串

        //"<html>\r\n<head>\r\n<meta http-equiv=\"content-type\" content=\"text/html; charset=gb2312\">\r\n<title> 

        //您的IP地址 </title>\r\n</head>\r\n<body style=\"margin:0px\"><center>您的IP是：[218.104.71.178] 来自：安徽省合肥市 联通</center></body></html>"

        /// <summary>

        /// 获取外网ip地址

        /// </summary>

        public string[] GetExtenalIpAddress()
        {

            string[] IP = new string[] { "未获取到外网ip", "" };
            string address = "http://1111.ip138.com/ic.asp";

            string str = GetWebStr(address);
            try
            {

                //提取外网ip数据 [218.104.71.178]

                int i1 = str.IndexOf("[") + 1, i2 = str.IndexOf("]");

                IP[0] = str.Substring(i1, i2 - i1);





                //提取网址说明信息 "来自：安徽省合肥市 联通"

                i1 = i2 + 2; i2 = str.IndexOf("<", i1);

                IP[1] = str.Substring(i1, i2 - i1);

            }

            catch (Exception) { }





            return IP;

        }





        /// <summary>

        /// 获取网址address的返回的文本串数据

        /// </summary>

        public string GetWebStr(string address)
        {

            string str = "";

            try
            {

                //从网址中获取本机ip数据

                System.Net.WebClient client = new System.Net.WebClient();

                client.Encoding = System.Text.Encoding.Default;

                str = client.DownloadString(address);

                client.Dispose();

            }

            catch (Exception) { }





            return str;

        }





        /// <summary>

        /// 获取本机的MAC;  //在项目-》添加引用....里面引用System.Management

        /// </summary>

        public string GetLocalMac()
        {

            string mac = null;

            ManagementObjectSearcher query = new ManagementObjectSearcher("SELECT * FROM Win32_NetworkAdapterConfiguration");

            ManagementObjectCollection queryCollection = query.Get();

            foreach (ManagementObject mo in queryCollection)
            {

                if (mo["IPEnabled"].ToString() == "True")

                    mac = mo["MacAddress"].ToString();

            }

            return (mac);

        }





        //只能获取同网段的远程主机MAC地址. 因为在标准网络协议下，ARP包是不能跨网段传输的，故想通过ARP协议是无法查询跨网段设备MAC地址的。

        [DllImport("Iphlpapi.dll")]

        private static extern int SendARP(Int32 dest, Int32 host, ref Int64 mac, ref Int32 length);

        [DllImport("Ws2_32.dll")]

        private static extern Int32 inet_addr(string ip);

        /// <summary>

        /// 获取ip对应的MAC地址

        /// </summary>

        public string GetMacAddress(string ip)
        {

            Int32 ldest = inet_addr(ip);            //目的ip 

            Int32 lhost = inet_addr("127.0.0.1");   //本地ip 





            try
            {

                Int64 macinfo = new Int64();

                Int32 len = 6;

                int res = SendARP(ldest, 0, ref macinfo, ref len);  //使用系统API接口发送ARP请求，解析ip对应的Mac地址

                return Convert.ToString(macinfo, 16);

            }

            catch (Exception err)
            {

                Console.WriteLine("Error:{0}", err.Message);

            }

            return "获取Mac地址失败";

        }





        /// <summary>

        /// 获取主板序列号

        /// </summary>

        /// <returns></returns>

        public string GetBIOSSerialNumber()
        {

            try
            {

                ManagementObjectSearcher searcher = new ManagementObjectSearcher("Select * From Win32_BIOS");

                string sBIOSSerialNumber = "";

                foreach (ManagementObject mo in searcher.Get())
                {

                    sBIOSSerialNumber = mo["SerialNumber"].ToString().Trim();

                }

                return sBIOSSerialNumber;

            }

            catch
            {

                return "";

            }

        }





        /// <summary>

        /// 获取CPU序列号

        /// </summary>

        /// <returns></returns>

        public string GetCPUSerialNumber()
        {

            try
            {

                ManagementObjectSearcher searcher = new ManagementObjectSearcher("Select * From Win32_Processor");

                string sCPUSerialNumber = "";

                foreach (ManagementObject mo in searcher.Get())
                {

                    sCPUSerialNumber = mo["ProcessorId"].ToString().Trim();

                }

                return sCPUSerialNumber;

            }

            catch
            {

                return "";

            }

        }

        //获取硬盘序列号

        public string GetHardDiskSerialNumber()
        {

            try
            {

                ManagementObjectSearcher searcher = new ManagementObjectSearcher("SELECT * FROM Win32_PhysicalMedia");

                string sHardDiskSerialNumber = "";

                foreach (ManagementObject mo in searcher.Get())
                {

                    sHardDiskSerialNumber = mo["SerialNumber"].ToString().Trim();

                    break;

                }

                return sHardDiskSerialNumber;

            }

            catch
            {

                return "";

            }

        }





        //获取网卡地址

        public string GetNetCardMACAddress()
        {

            try
            {

                ManagementObjectSearcher searcher = new ManagementObjectSearcher("SELECT * FROM Win32_NetworkAdapter WHERE ((MACAddress Is Not NULL) AND (Manufacturer <> 'Microsoft'))");

                string NetCardMACAddress = "";

                foreach (ManagementObject mo in searcher.Get())
                {

                    NetCardMACAddress = mo["MACAddress"].ToString().Trim();

                }

                return NetCardMACAddress;

            }

            catch
            {

                return "";

            }

        }









        /// <summary>

        /// 获得CPU编号

        /// </summary>

        public string GetCPUID()
        {

            string cpuid = "";

            ManagementClass mc = new ManagementClass("Win32_Processor");

            ManagementObjectCollection moc = mc.GetInstances();

            foreach (ManagementObject mo in moc)
            {

                cpuid = mo.Properties["ProcessorId"].Value.ToString();

            }

            return cpuid;

        }





        /// <summary>

        /// 获取硬盘序列号

        /// </summary>

        public string GetDiskSerialNumber()
        {

            //这种模式在插入一个U盘后可能会有不同的结果，如插入我的手机时

            String HDid = "";

            ManagementClass mc = new ManagementClass("Win32_DiskDrive");

            ManagementObjectCollection moc = mc.GetInstances();

            foreach (ManagementObject mo in moc)
            {

                HDid = (string)mo.Properties["Model"].Value;//SerialNumber

                break;//这名话解决有多个物理盘时产生的问题，只取第一个物理硬盘

            }

            return HDid;





            /*ManagementClass mc = new ManagementClass("Win32_PhysicalMedia");

            ManagementObjectCollection moc = mc.GetInstances();

            string str = "";

            foreach (ManagementObject mo in moc)

            {

                str = mo.Properties["SerialNumber"].Value.ToString();

                break;

            }

            return str;*/

        }





        /// <summary>

        /// 获取网卡硬件地址

        /// </summary>

        public string GetMacAddress()
        {

            string mac = "";

            ManagementClass mc = new ManagementClass("Win32_NetworkAdapterConfiguration");

            ManagementObjectCollection moc = mc.GetInstances();

            foreach (ManagementObject mo in moc)
            {

                if ((bool)mo["IPEnabled"] == true)
                {

                    mac = mo["MacAddress"].ToString();

                    break;

                }

            }

            return mac;

        }





        /// <summary>

        /// 获取IP地址

        /// </summary>

        public string GetIPAddress()
        {

            string st = "";

            ManagementClass mc = new ManagementClass("Win32_NetworkAdapterConfiguration");

            ManagementObjectCollection moc = mc.GetInstances();

            foreach (ManagementObject mo in moc)
            {

                if ((bool)mo["IPEnabled"] == true)
                {

                    //st=mo["IpAddress"].ToString(); 

                    System.Array ar;

                    ar = (System.Array)(mo.Properties["IpAddress"].Value);

                    st = ar.GetValue(0).ToString();

                    break;

                }

            }

            return st;

        }





        /// <summary>

        /// 操作系统的登录用户名

        /// </summary>

        public string GetUserName()
        {

            return Environment.UserName;

        }









        /// <summary>

        /// 获取计算机名

        /// </summary>

        public string GetComputerName()
        {

            return Environment.MachineName;

        }





        /// <summary>

        /// 操作系统类型

        /// </summary>

        public string GetSystemType()
        {

            string st = "";

            ManagementClass mc = new ManagementClass("Win32_ComputerSystem");

            ManagementObjectCollection moc = mc.GetInstances();

            foreach (ManagementObject mo in moc)
            {

                st = mo["SystemType"].ToString();

            }

            return st;

        }





        /// <summary>

        /// 物理内存

        /// </summary>

        public string GetPhysicalMemory()
        {

            string st = "";

            ManagementClass mc = new ManagementClass("Win32_ComputerSystem");

            ManagementObjectCollection moc = mc.GetInstances();

            foreach (ManagementObject mo in moc)
            {

                st = mo["TotalPhysicalMemory"].ToString();

            }

            return st;

        }





        /// <summary>

        /// 显卡PNPDeviceID

        /// </summary>

        public string GetVideoPNPID()
        {

            string st = "";

            ManagementObjectSearcher mos = new ManagementObjectSearcher("Select * from Win32_VideoController");

            foreach (ManagementObject mo in mos.Get())
            {

                st = mo["PNPDeviceID"].ToString();

            }

            return st;

        }





        /// <summary>

        /// 声卡PNPDeviceID

        /// </summary>

        public string GetSoundPNPID()
        {

            string st = "";

            ManagementObjectSearcher mos = new ManagementObjectSearcher("Select * from Win32_SoundDevice");

            foreach (ManagementObject mo in mos.Get())
            {

                st = mo["PNPDeviceID"].ToString();

            }

            return st;

        }





        /// <summary>

        /// CPU版本信息

        /// </summary>

        public string GetCPUVersion()
        {

            string st = "";

            ManagementObjectSearcher mos = new ManagementObjectSearcher("Select * from Win32_Processor");

            foreach (ManagementObject mo in mos.Get())
            {

                st = mo["Version"].ToString();

            }

            return st;

        }





        /// <summary>

        /// CPU名称信息

        /// </summary>

        public string GetCPUName()
        {

            string st = "";

            ManagementObjectSearcher driveID = new ManagementObjectSearcher("Select * from Win32_Processor");

            foreach (ManagementObject mo in driveID.Get())
            {

                st = mo["Name"].ToString();

            }

            return st;

        }





        /// <summary>

        /// CPU制造厂商

        /// </summary>

        public string GetCPUManufacturer()
        {

            string st = "";

            ManagementObjectSearcher mos = new ManagementObjectSearcher("Select * from Win32_Processor");

            foreach (ManagementObject mo in mos.Get())
            {

                st = mo["Manufacturer"].ToString();

            }

            return st;

        }





        /// <summary>

        /// 主板制造厂商

        /// </summary>

        public string GetBoardManufacturer()
        {

            SelectQuery query = new SelectQuery("Select * from Win32_BaseBoard");

            ManagementObjectSearcher mos = new ManagementObjectSearcher(query);

            ManagementObjectCollection.ManagementObjectEnumerator data = mos.Get().GetEnumerator();

            data.MoveNext();

            ManagementBaseObject board = data.Current;

            return board.GetPropertyValue("Manufacturer").ToString();

        }





        /// <summary>

        /// 主板编号

        /// </summary>

        public string GetBoardID()
        {

            string st = "";

            ManagementObjectSearcher mos = new ManagementObjectSearcher("Select * from Win32_BaseBoard");

            foreach (ManagementObject mo in mos.Get())
            {

                st = mo["SerialNumber"].ToString();

            }

            return st;

        }





        /// <summary>

        /// 主板型号

        /// </summary>

        public string GetBoardType()
        {

            string st = "";

            ManagementObjectSearcher mos = new ManagementObjectSearcher("Select * from Win32_BaseBoard");

            foreach (ManagementObject mo in mos.Get())
            {

                st = mo["Product"].ToString();

            }

            return st;

        }

    }

}



