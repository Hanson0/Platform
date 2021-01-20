using System.Collections.Generic;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Instrument.Far.Property;
using AILinkFactoryAuto.Task;
using AILinkFactoryAuto.Task.Executer;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.Utils;

namespace AILinkFactoryAuto.Instrument.Far.Executer
{
    public class OpenInstrumentExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            InstrumentProperties config = properties as InstrumentProperties;
            ILogFile logFile = new LogFile(config.LogPath + "//" + TimeUtils.GetCurrentDate() + ".log");
            Visa visa = new Visa(logFile);
            visa.Connect(config.Resource);

            GlobalVaribles configGlobal = globalDic[typeof(GlobalVaribles).ToString()] as GlobalVaribles;
            configGlobal.Add("InstrumentType", config.InstrumentType.ToString());

            globalDic.Put(visa);
        }
    }
}
