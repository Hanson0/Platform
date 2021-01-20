using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using AILinkFactoryAuto.Task;

namespace AILinkFactoryAuto.Utils
{
    public class TimeUtils
    {
        public static string GetCurrentDate()
        {
            return DateTime.Now.ToString("yyyy-MM-dd_HH-mm-ss");
        }

        //public static void Execute(Func<bool> func, int ms, int interval = 100)
        //{
        //    bool result = System.Threading.Tasks.Task.Factory.StartNew(() =>
        //    {
        //        while (true)
        //        {
        //            try
        //            {
        //                if (func.Invoke())
        //                {
        //                    break;
        //                }
        //            }
        //            catch (Exception e)
        //            {
        //                Console.WriteLine(e);
        //            }

        //            Thread.Sleep(interval);
        //        }

        //    }).Wait(ms);
        //    if (!result)
        //    {
        //        throw new BaseException("超时：" + func);
        //    }
        //}

        public static void Execute(Func<bool> func, int ms, int interval = 100)
        {
            DateTime start = DateTime.Now;
            DateTime now = DateTime.Now;
            TimeSpan timeSpan = now - start;
            while (timeSpan.TotalMilliseconds <= ms)
            {
                try
                {
                    if (func.Invoke())
                    {
                        break;
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                }

                Thread.Sleep(interval);
                now = DateTime.Now;
                timeSpan = now - start;
            }

            if (timeSpan.TotalMilliseconds > ms)
            {
                throw new BaseException("超时：" + func);
            }
        }
    }
}
