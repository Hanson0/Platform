using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using AILinkFactoryAuto.Core;
using Ivi.Visa;

namespace AILinkFactoryAuto.Instrument.Far
{
    public class Visa
    {
        //private Semaphore semaphore = new Semaphore(1, 1);
        //private int timeout = 10000;

        private ILogFile logFile;

        private IMessageBasedSession instrument;

        private string resource;

        public Visa(ILogFile logFile)
        {
            this.logFile = logFile;
        }
        public void Connect(string resource)
        {
            this.resource = resource;
            instrument = GlobalResourceManager.Open(this.resource) as IMessageBasedSession;
            instrument.Clear();
            Read("*IDN?");
        }

        private bool IsDisposed()
        {
            Type type = instrument.GetType();
            PropertyInfo propertyInfo = type.GetProperty("IsDisposed");
            bool isDisposed = (bool)propertyInfo.GetValue(instrument, null);
            return isDisposed;
        }

        public void Close()
        {
            //if (semaphore.WaitOne(timeout))
            //{
            //    instrument.Dispose();
            //    semaphore.Release();
            //}
            instrument.Dispose();
        }

        public void Write(string cmd)
        {
            //if (semaphore.WaitOne(timeout))
            //{
            //    if (!IsDisposed())
            //    {
            //        logFile.AppendLine(string.Format("->[{0}]{1}", this.resource, cmd));
            //        instrument.RawIO.Write(cmd + "\r\n");
            //    }
            //    semaphore.Release();
            //}
            logFile.AppendLine(string.Format("->[{0}]{1}", this.resource, cmd));
            instrument.RawIO.Write(cmd + "\r\n");
        }

        //public string Query(string cmd)
        //{
        //    logFile.AppendLine(string.Format("<-[{0}]{1}", this.resource, cmd));
        //    instrument.RawIO.Write(cmd + "\r\n");
        //    string response = instrument.RawIO.ReadString();
        //    logFile.AppendLine(string.Format("<-[{0}]{1}", this.resource, response));
        //    return response;
        //}

        public VisaResponse Read(string cmd)
        {
            //string response = null;
            //if (semaphore.WaitOne())
            //{
            //    if (!IsDisposed())
            //    {
            //        logFile.AppendLine(string.Format("<-[{0}]{1}", this.resource, cmd));
            //        instrument.RawIO.Write(cmd + "\r\n");
            //        response = instrument.RawIO.ReadString();
            //        logFile.AppendLine(string.Format("<-[{0}]{1}", this.resource, response));
            //    }
            //    semaphore.Release();
            //}
            //return new VisaResponse(response);

            logFile.AppendLine(string.Format("<-[{0}]{1}", this.resource, cmd));
            instrument.RawIO.Write(cmd + "\r\n");
            string response = instrument.RawIO.ReadString();
            logFile.AppendLine(string.Format("<-[{0}]{1}", this.resource, response));
            return new VisaResponse(response);
        }
    }
}
