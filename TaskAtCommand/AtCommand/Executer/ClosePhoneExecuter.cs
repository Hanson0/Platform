using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Dut.AtCommand.Property;
using AILinkFactoryAuto.Task;
using AILinkFactoryAuto.Task.Executer;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Dut.AtCommand.Executer
{
    public class ClosePhoneExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            List<ComDut> comDutList = globalDic[typeof(List<ComDut>).ToString()] as List<ComDut>;
            ClosePhoneProperties config = properties as ClosePhoneProperties;
            //ComDut comDut = globalDic[typeof(ComDut).ToString()] as ComDut;
            ComDut comDut = null;
            foreach (var item in comDutList)
            {
                if (item.PortName == config.PortName)
                {
                    comDut = item;
                    break;
                }

            }
            if (comDut == null)
            {
                throw new BaseException(string.Format("ClosePhoneProperties No PortName:{0}", config.PortName));
            }

            try
            {
                comDut.Close();
                comDut.Dispose();

                comDutList.Remove(comDut);
                //globalDic.Remove(typeof(ComDut).ToString());
                //globalDic.Remove(typeof(OpenPhoneProperties).ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }
    }
}
