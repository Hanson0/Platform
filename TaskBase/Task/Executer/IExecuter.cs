using System.Collections.Generic;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Task.Executer
{
    public interface IExecuter
    {
        void Run(IProperties properties, GlobalDic<string, object> globalDic);
    }
}
