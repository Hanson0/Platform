using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using log4net.Appender;
using log4net.Core;

namespace AILinkFactoryAuto.Core
{
    public class UiLogAppender : AppenderSkeleton
    {
        public event EventHandler<UiLogEventArgs> UiLogReceived;

        protected override void Append(LoggingEvent loggingEvent)
        {
            var message = RenderLoggingEvent(loggingEvent);
            OnUiLogReceived(new UiLogEventArgs(message));
        }

        protected virtual void OnUiLogReceived(UiLogEventArgs e)
        {
            if (UiLogReceived != null)
                UiLogReceived(this, e);
        }
        
    }
}
