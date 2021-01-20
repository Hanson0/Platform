using System;
using System.Collections.Generic;
using AILinkFactoryAuto.Task;
using AILinkFactoryAuto.Task.Executer;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Instrument.Far.Executer
{
    public class CloseInstrumentExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            try
            {
                Visa visa = globalDic[typeof(Visa).ToString()] as Visa;
                //visa.Write("*RST");
                //visa.Write("*CLS");
                visa.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }
    }
}
