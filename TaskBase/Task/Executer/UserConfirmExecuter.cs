using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.View;

namespace AILinkFactoryAuto.Task.Executer
{
    public class UserConfirmExecuter : IExecuter
    {
        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            UserConfirmProperties config = properties as UserConfirmProperties;
            ILog log = globalDic.Get<ILog>();

            FormUserConfirm formUserConfirm = new FormUserConfirm(config, log)
            {
                StartPosition = FormStartPosition.CenterScreen
            };
            formUserConfirm.ShowDialog();

            if (!formUserConfirm.Result)
            {
                throw new BaseException("User Confirm Fail");
            }
        }
    }
}
