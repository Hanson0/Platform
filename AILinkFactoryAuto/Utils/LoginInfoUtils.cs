using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Utils
{
    class LoginInfoUtils
    {
        [Serializable]
        public class Root
        {
            /// <summary>
            /// 
            /// </summary>
            public string phone { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string loginName { get; set; }
            /// <summary>
            /// 用户名
            /// </summary>
            public string name { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public List<MenuItem> menu { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string userId { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string email { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string token { get; set; }
        }
        public class MenuItem
        {
            /// <summary>
            /// 
            /// </summary>
            public List<string> appFuncs { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int factoryId { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public List<PcFuncsItem> pcFuncs { get; set; }
            /// <summary>
            /// 工厂名
            /// </summary>
            public string factoryName { get; set; }
        }

        public class PcFuncsItem
        {
            /// <summary>
            /// 
            /// </summary>
            public int clientType { get; set; }
            /// <summary>
            /// 软件配置
            /// </summary>
            public string name { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string remark { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string id { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int orgId { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string parentId { get; set; }
        }



    }
}
