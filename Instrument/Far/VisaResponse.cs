using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Instrument.Far
{
    public class VisaResponse
    {
        private string response;

        private string[] rawDataArray;

        public VisaResponse(string response)
        {
            this.response = response;
        }

        public string Get(int location)
        {
            return rawDataArray[location - 1];
        }

        public bool Contains(string value)
        {
            if (string.IsNullOrEmpty(response))
            {
                return false;
            }
            return response.Contains(value);
        }

        public VisaResponse Split()
        {
            if (string.IsNullOrEmpty(response))
            {
                return null;
            }

            rawDataArray = response.Split(new char[] { ',' });
            return this;
        }
    }
}
