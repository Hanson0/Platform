using System.ComponentModel;

namespace AILinkFactoryAuto.Task.Property
{
    public enum ExecuteCondition
    {
        ALWAYS,
        PASS,
        //FAIL
    }

    public class CommonProperties : IProperties
    {
        private ExecuteCondition executeCondition = ExecuteCondition.PASS;

        private int timeout = 1000;

        private int sleepTimeBefore;

        private int sleepTimeAfter;

        private int retryCount = 3;

        private int retryInterval = 200;

        [Description("execute condition")]
        public ExecuteCondition ExecuteCondition
        {
            get { return executeCondition; }
            set { executeCondition = value; }
        }

        [Description("timeout, unit: ms")]
        public int Timeout
        {
            get { return timeout; }
            set { timeout = value; }
        }

        public int SleepTimeBefore
        {
            get { return sleepTimeBefore; }
            set { sleepTimeBefore = value; }
        }

        public int SleepTimeAfter
        {
            get { return sleepTimeAfter; }
            set { sleepTimeAfter = value; }
        }

        public int RetryCount
        {
            get { return retryCount; }
            set { retryCount = value; }
        }

        public int RetryInterval
        {
            get { return retryInterval; }
            set { retryInterval = value; }
        }
    }
}
