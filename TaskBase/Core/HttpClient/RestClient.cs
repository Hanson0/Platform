using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using AILinkFactoryAuto.Utils;

namespace AILinkFactoryAuto.Core.HttpClient
{
    public class RestClient : IRestClient
    {
        public ContentType ContentType { get; set; }

        public Hashtable Headers { get; set; }

        public int Timeout { get; set; }

        public RestClient()
        {
            Timeout = 6000;
            Headers = new Hashtable();
        }

        public void AddHeader(string name, string value)
        {
            if (string.IsNullOrEmpty(name) || string.IsNullOrEmpty(value))
            {
                return;
            }
            Headers.Add(name, value);
        }

        public IRestResponse Post(string url, string body)
        {
            return Execute(url, HttpMethod.POST, null, body);
        }

        public IRestResponse Post(string url)
        {
            return Execute(url, HttpMethod.POST, null, null);
        }

        public IRestResponse Get(string url)
        {
            return Execute(url, HttpMethod.GET, null, null);
        }

        public IRestResponse Get(string url, RestParam restParam)
        {
            return Execute(url, HttpMethod.GET, restParam, null);
        }

        private string GenParam(RestParam restParam)
        {
            if (restParam == null)
            {
                return null;
            }

            bool isFist = true;
            string tempParam = null;
            foreach (var param in restParam)
            {
                if (isFist)
                {
                    tempParam = tempParam + "?" + param.Key + "=" + param.Value;
                    isFist = false;
                }
                else
                {
                    tempParam = tempParam + "&" + param.Key + "=" + param.Value;
                }
            }

            return tempParam;
        }

        private IRestResponse Execute(string url, HttpMethod httpMethod, RestParam restParam, string body)
        {
            IRestResponse restResponse = new RestResponse();

            if (restParam != null)
            {
                string tempParam = GenParam(restParam);
                url = url + tempParam;
            }

            LogUtils.UiDebug.DebugFormat("HTTP Method {0} url={1} body={2}", httpMethod, url, body);

            HttpWebRequest httpWebRequest = (HttpWebRequest)WebRequest.Create(url);
            httpWebRequest.ServicePoint.Expect100Continue = false;
            httpWebRequest.ContentType = ContentType.ToString();
            httpWebRequest.Method = httpMethod.ToString();
            httpWebRequest.Timeout = Timeout;
            foreach (DictionaryEntry enty in Headers)
            {
                httpWebRequest.Headers.Add(enty.Key.ToString(), enty.Value.ToString());
            }
            HttpWebResponse httpWebResponse = null;
            StreamReader streamReader = null;
            string responseContent = null;
            try
            {
                if (body != null)
                {
                    byte[] buffer = Encoding.UTF8.GetBytes(body);
                    httpWebRequest.ContentLength = buffer.Length;
                    httpWebRequest.GetRequestStream().Write(buffer, 0, buffer.Length);
                }

                httpWebResponse = (HttpWebResponse)httpWebRequest.GetResponse();
                streamReader = new StreamReader(httpWebResponse.GetResponseStream());
                responseContent = streamReader.ReadToEnd();
            }
            catch (WebException e)
            {
                httpWebResponse = (HttpWebResponse)e.Response;
                if (httpWebResponse != null)
                {
                    streamReader = new StreamReader(httpWebResponse.GetResponseStream());
                    responseContent = streamReader.ReadToEnd();
                }
                else
                {
                    restResponse.SetErrorMessage(e.Message);
                }
            }
            catch (Exception e)
            {
                restResponse.SetErrorMessage(e.Message);
            }

            if (httpWebResponse != null)
            {
                restResponse.SetHttpStatusCode(httpWebResponse.StatusCode);
            }
            restResponse.SetResponseBody(responseContent);

            if (httpWebResponse != null)
            {
                httpWebResponse.Close();
            }

            if (streamReader != null)
            {
                streamReader.Close();
            }

            if (httpWebRequest != null)
            {
                httpWebRequest.Abort();
            }

            LogUtils.UiDebug.DebugFormat("HTTP POST httpStatusCode={0} responseBody={1}", restResponse.GetHttpStatusCode(), restResponse.GetResponseBody());

            return restResponse;
        }
    }
}
