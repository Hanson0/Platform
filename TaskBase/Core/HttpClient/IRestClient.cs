using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Core.HttpClient
{
    public interface IRestClient
    {
        ContentType ContentType { get; set; }

        void AddHeader(string name, string value);

        IRestResponse Post(string url);

        IRestResponse Post(string url, string body);

        IRestResponse Get(string url);

        IRestResponse Get(string url, RestParam restParam);

    }
}
