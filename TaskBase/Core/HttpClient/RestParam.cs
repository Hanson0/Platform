using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Core.HttpClient
{
    public class RestParam : Dictionary<string, string>
    {
        public RestParam Put(string name, string value)
        {
            this.Add(name, value);
            return this;
        }
    }
}
