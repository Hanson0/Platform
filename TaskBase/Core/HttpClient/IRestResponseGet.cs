using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;

namespace AILinkFactoryAuto.Core.HttpClient
{
    public interface IRestResponseGet
    {
        string GetErrorMessage();

        string GetResponseBody();

        HttpStatusCode GetHttpStatusCode();
    }
}
