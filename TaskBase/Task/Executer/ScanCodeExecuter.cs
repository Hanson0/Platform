using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.Utils;
using AILinkFactoryAuto.View;

namespace AILinkFactoryAuto.Task.Executer
{
    public class ScanCodeExecuter : IExecuter
    {
        private static object myLock = new object();

        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            ScanCodeProperties config = properties as ScanCodeProperties;
            GlobalVaribles configGv = globalDic.Get<GlobalVaribles>();
            CountLatch sync = globalDic.Get<CountLatch>();

            if (config.Order > 0)
            {
                try
                {
                    TimeUtils.Execute(() =>
                    {
                        if (sync.GetCurrent("ScanCodeExecuter") == config.Order)
                        {
                            return true;
                        }

                        return false;
                    }, config.Timeout);
                }
                catch (Exception e)
                {
                    sync.CountDown("ScanCodeExecuter");
                    throw e;
                }
            }

            FormScanCode formScanCode = new FormScanCode()
            {
                DutName = config.DutName,
                ShowInTaskbar = true,
                StartPosition = FormStartPosition.CenterScreen
            };
            DialogResult dialogResult = DialogResult.None;
            lock (myLock)
            {
                dialogResult = formScanCode.ShowDialog();
            }
            if (dialogResult != DialogResult.OK)
            {
                sync.CountDown("ScanCodeExecuter");
                throw new BaseException("user discard scan code");
            }
            configGv.Add(GlobalVaribles.LABEL_SN, formScanCode.LabelSn);

            if (sync != null)
            {
                sync.CountDown("ScanCodeExecuter");

                TimeUtils.Execute(() =>
                {
                    if (sync.GetCount("ScanCodeExecuter") == 0)
                    {
                        return true;
                    }

                    return false;
                }, config.Timeout);
            }
        }
    }
}
