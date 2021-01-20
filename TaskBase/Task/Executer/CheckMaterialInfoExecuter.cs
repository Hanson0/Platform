using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Task.Property;
using Mes.Test;
using Newtonsoft.Json.Linq;
using AILinkFactoryAuto.Core;

namespace AILinkFactoryAuto.Task.Executer
{
    public class CheckMaterialInfoExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            CheckMaterialInfoProperties config = properties as CheckMaterialInfoProperties;
            ILog log = globalDic.Get<ILog>();
            GlobalVaribles gv = globalDic.Get<GlobalVaribles>();
            log.Info("MaterialCode:" + config.MaterialCode);
            log.Info("MaterialModel:" + config.MaterialModel);

            string sn = gv.Get(GlobalVaribles.MAC);
            string json = MesProcess.FindInfoBySn(sn);

            JObject response = JObject.Parse(json);
            JObject product = response["product"] as JObject;
            string materialCode = product["itemNo"].ToString();
            string materialModel = product["model"].ToString();

            if (config.MaterialCode != materialCode || config.MaterialModel != materialModel)
            {
                string msg = "materialCode=" + materialCode + "\r\n";
                msg += "materialModel=" + materialModel + "\r\n";
                throw new Exception(msg);
            }
        }
    }
}
