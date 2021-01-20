using System;
using System.Collections.Generic;
using System.Linq;
using System.Management;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.Core;

namespace AILinkFactoryAuto.Task.Executer
{
    public class ReadMacNetCardExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            ReadMacNetCardProperties config = properties as ReadMacNetCardProperties;
            ILog log = globalDic.Get<ILog>();
            string mac = GetMacByWmi(config.NetCardName);
            log.Info(config.NetCardName + " MAC=" + mac);

            GlobalVaribles gv = globalDic.Get<GlobalVaribles>();
            gv.Add(GlobalVaribles.MAC, mac);
        }

        private string GetMacByWmi(string netCardName)
        {
            NetworkInterface[] networkInterfaces = NetworkInterface.GetAllNetworkInterfaces();
            foreach (NetworkInterface networkInterface in networkInterfaces)
            {
                if (networkInterface.Description == netCardName && networkInterface.Id != "")
                {
                    return networkInterface.GetPhysicalAddress().ToString();
                }
            }

            throw new BaseException("read mac fail");
        }
    }
}
