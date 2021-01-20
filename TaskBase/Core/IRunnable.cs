using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Task;

namespace AILinkFactoryAuto.Core
{
    public delegate void StartHandler();

    public delegate void StopHandler(bool result);

    public interface IRunnable
    {
        CountLatch Sync { get; set; }

        string ThreadName { get; set; } 

        bool IsRunning { get; }

        void Stop();

        void Start();

        void Run();

        StartHandler StartHandler { get; set; }

        StopHandler StopHandler { get; set; }
    }
}
