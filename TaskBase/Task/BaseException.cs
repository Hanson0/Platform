using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task
{
    public class BaseException : Exception
    {
        public BaseException(string message) : base(message)
        {
            
        }

        public BaseException() : base()
        {

        }
    }
}
