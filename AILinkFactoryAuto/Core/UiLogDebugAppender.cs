using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using log4net.Appender;
using log4net.Core;

namespace AILinkFactoryAuto.Core
{
    public class UiLogDebugAppender : AppenderSkeleton
    {
        public event EventHandler<UiLogEventArgs> UiLogReceived;

        protected override void Append(LoggingEvent loggingEvent)
        {
            var message = RenderLoggingEvent(loggingEvent);
            string name = Thread.CurrentThread.Name;
            int threadId = Thread.CurrentThread.ManagedThreadId;
            OnUiLogReceived(new UiLogEventArgs(message));
        }

        protected virtual void OnUiLogReceived(UiLogEventArgs e)
        {
            if (UiLogReceived != null)
                UiLogReceived(this, e);
        }
        
    }
}
