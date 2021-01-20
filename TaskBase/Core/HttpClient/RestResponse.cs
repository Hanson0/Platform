using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;

namespace AILinkFactoryAuto.Core.HttpClient
{
    class RestResponse : IRestResponse
    {
        private HttpStatusCode _httpStatusCode;

        private string _errorMessage;

        private string _responseBody;

        public HttpStatusCode GetHttpStatusCode()
        {
            return _httpStatusCode;
        }

        public void SetHttpStatusCode(HttpStatusCode httpStatusCode)
        {
            _httpStatusCode = httpStatusCode;
        }

        public string GetErrorMessage()
        {
            return _errorMessage;
        }

        public void SetErrorMessage(string errorMessage)
        {
            _errorMessage = errorMessage;
        }

        public string GetResponseBody()
        {
            return _responseBody;
        }

        public void SetResponseBody(string responseBody)
        {
            _responseBody = responseBody;
        }
    }
}
