using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Core
{
    public class UiLogEventArgs : EventArgs
    {
        public string Message { get; private set; }

        public UiLogEventArgs(string message)
        {
            Message = message;
        }
    }
}
