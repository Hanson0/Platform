using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using log4net;
using log4net.Repository.Hierarchy;

namespace AILinkFactoryAuto.Utils
{
    public class LogUtils
    {
        public static ILog UiInfo = LogManager.GetLogger("UiInfo");

        public static ILog UiDebug = LogManager.GetLogger("UiDebug");

        public static T GetAppender<T>() where T : class
        {
            var hierarchy = LogManager.GetRepository() as Hierarchy;
            if (hierarchy != null)
            {
                var appenders = hierarchy.Root.Repository.GetAppenders();
                foreach (var appender in appenders)
                {
                    T t = appender as T;
                    if (t != null)
                    {
                        return t;
                    }
                }
            }

            return null;
        }
    }
}
