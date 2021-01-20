using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Core.Loss;
using AILinkFactoryAuto.Instrument.Property;
using AILinkFactoryAuto.Properties;
using AILinkFactoryAuto.Task;
using DevExpress.Spreadsheet;

namespace AILinkFactoryAuto.View
{
    public partial class FormCableLoss : Form
    {
        private List<TaskItem> taskItemList;

        public List<TaskItem> TaskItemList
        {
            get { return taskItemList; }
            set { taskItemList = value; }
        }

        public FormCableLoss()
        {
            InitializeComponent();
        }

        private void FormCableLoss_Load(object sender, EventArgs e)
        {
            this.Icon = Resources.phone;

            this.Shown += FormCableLoss_Shown;
            this.Closed += FormCableLoss_Closed;

            btnCancel.Click += BtnCancel_Click;
            btnLoad.Click += BtnLoad_Click;
        }

        private void BtnLoad_Click(object sender, EventArgs e)
        {
            try
            {
                CableLoss cableLoss = new CableLoss();
                Worksheet worksheet = spreadsheetControl.ActiveWorksheet;
                int row = 1;
                do
                {
                    string port = worksheet.GetCellValue(0, row).ToString();
                    string freqStart = worksheet.GetCellValue(1, row).ToString();
                    string freqEnd = worksheet.GetCellValue(2, row).ToString();
                    string loss = worksheet.GetCellValue(3, row).ToString();

                    if (string.IsNullOrEmpty(port))
                    {
                        break;
                    }

                    CableLossItem cableLossItem = new CableLossItem();
                    cableLossItem.CmwPort = (CmwPort)Enum.Parse(typeof(CmwPort), port);
                    cableLossItem.FreqStart = double.Parse(freqStart);
                    cableLossItem.FreqEnd = double.Parse(freqEnd);
                    cableLossItem.Loss = double.Parse(loss);

                    cableLoss.Add(cableLossItem);
                    row++;
                } while (true);

                double freqIn = 0;
                double freqOut = 0;
                foreach (var taskItem in TaskItemList)
                {
                    InstrumentInitProperties init = taskItem.CommonProperties as InstrumentInitProperties;
                    if (init != null)
                    {
                        freqIn = init.FrequencyIn;
                        freqOut = init.FrequencyOut;

                        double loss = cableLoss.GetLoss(freqIn, init.CmwPortIn.CmwPort);
                        init.CmwPortIn.Attenuation = loss;

                        loss = cableLoss.GetLoss(freqOut, init.CmwPortOut.CmwPort);
                        init.CmwPortOut.Attenuation = loss;
                    }

                    InstrumentPlayWaveFileProperties playWaveFile = taskItem.CommonProperties as InstrumentPlayWaveFileProperties;
                    if (playWaveFile != null)
                    {
                        double loss = cableLoss.GetLoss(freqOut, playWaveFile.CmwPortOut.CmwPort);
                        playWaveFile.CmwPortOut.Attenuation = loss;
                    }
                }

                Box.ShowInfoOk("恭喜你，加载线损成功！");
            }
            catch (Exception exception)
            {
                Box.ShowWarnOkCancel("很遗憾，加载线损失败！\r\n" + exception.Message);
            }
            
        }

        private void BtnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void FormCableLoss_Closed(object sender, EventArgs e)
        {
            spreadsheetControl.SaveDocument();
        }

        private void FormCableLoss_Shown(object sender, EventArgs e)
        {
            spreadsheetControl.LoadDocument("./loss/cableloss.xlsx");           
        }
    }
}
