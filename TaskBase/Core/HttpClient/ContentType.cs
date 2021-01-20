using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Core.HttpClient
{
    public class ContentType
    {
        public static ContentType APPLICATION_JSON = Create("application/json", "utf-8");

        private string mimeType;

        private string charset;

        public string MimeType
        {
            get { return mimeType; }
        }

        public string Charset
        {
            get { return charset; }
        }

        public ContentType(string mimeType, string charset)
        {
            this.mimeType = mimeType;
            this.charset = charset;
        }

        public static ContentType Create(string mimeType, string charset)
        {
            ContentType contentType = new ContentType(mimeType, charset);
            return contentType;
        }

        public override string ToString()
        {
            if (!string.IsNullOrEmpty(this.mimeType) && !string.IsNullOrEmpty(this.charset))
            {
                return string.Format("{0}; charset={1}", mimeType, charset);
            }
            else if (!string.IsNullOrEmpty(this.mimeType))
            {
                return mimeType;
            }
            else
            {
                return null;
            }
        }
    }
}
