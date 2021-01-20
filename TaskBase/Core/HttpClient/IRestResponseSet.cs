using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;

namespace AILinkFactoryAuto.Core.HttpClient
{
    public interface IRestResponseSet
    {
        void SetErrorMessage(string errorMessage);

        void SetResponseBody(string responseBody);

        void SetHttpStatusCode(HttpStatusCode httpStatusCode);
    }
}
