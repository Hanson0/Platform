using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Core
{
    public class CountLatch
    {
        private uint originCount;

        private Dictionary<string, CountData> store = new Dictionary<string, CountData>();

        public uint OriginCount
        {
            get { return originCount; }
        }

        public CountLatch(uint count)
        {
            this.originCount = count;
        }

        public uint GetCount(string key)
        {
            lock (this)
            {
                Init(key);

                CountData countData = this.store[key];
                return countData.Count;
            }

        }

        public uint GetCurrent(string key)
        {
            lock (this)
            {
                Init(key);

                CountData countData = this.store[key];
                return countData.Current;
            }
        }

        public void CountDown(string key)
        {
            lock (this)
            {
                Init(key);

                CountData countData = this.store[key];
                countData.Count = countData.Count - 1;
                countData.Current = countData.Current + 1;
            }
        }

        private void Init(string key)
        {
            if (!this.store.ContainsKey(key))
            {
                this.store.Add(key, new CountData()
                {
                    Count = this.originCount,
                    Current = 1
                });
            }
        }

        private class CountData
        {
            private uint count;

            private uint current;

            public uint Count
            {
                get { return count; }
                set { count = value; }
            }

            public uint Current
            {
                get { return current; }
                set { current = value; }
            }
        }
    }
}
