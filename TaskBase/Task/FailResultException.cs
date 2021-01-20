using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task
{
    public class FailResultException : BaseException
    {
        public FailResultException() : base("result fail")
        {

        }
    }
}
