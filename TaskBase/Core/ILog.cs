using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Core
{
    public interface ILog
    {

        void Info(string log);

        void Fail(string log);

        void Pass(string log);

        void Warn(string log);
    }
}
