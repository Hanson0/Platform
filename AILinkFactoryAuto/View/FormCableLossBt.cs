using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using AILinkFactoryAuto.Core;
using DevExpress.Spreadsheet;

namespace AILinkFactoryAuto.View
{
    public partial class FormCableLossBt : Form
    {
        public FormCableLossBt()
        {
            InitializeComponent();
            spreadsheetControl1.LoadDocument("./loss/cableloss_bt.xlsx");
        }

        //加载按钮点击事件
        private void button1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(fileText.Text))
            {
                Box.ShowWarnOkCancel("请选择线损配置文件!");
                return;
            }
            try
            {
                spreadsheetControl1.SaveDocument("./loss/cableloss_bt.xlsx");
                Worksheet worksheet = spreadsheetControl1.ActiveWorksheet;
                int row = 1;
                //读取excel的数据
                List<Dictionary<string, string>> mainList = new List<Dictionary<string, string>>();
                List<Dictionary<string, string>> divList = new List<Dictionary<string, string>>();
                List<Dictionary<string, string>> gpsList = new List<Dictionary<string, string>>();
                do
                {
                    string category = worksheet.GetCellValue(0, row).ToString();
                    string freqStart = worksheet.GetCellValue(1, row).ToString();
                    string freqEnd = worksheet.GetCellValue(2, row).ToString();
                    string loss = worksheet.GetCellValue(3, row).ToString();
                    if (string.IsNullOrEmpty(category))
                    {
                        break;
                    }
                    Dictionary<string, string> dictionary = new Dictionary<string, string>();
                    dictionary.Add("freqStart", freqStart);
                    dictionary.Add("freqEnd", freqEnd);
                    dictionary.Add("loss", loss);
                    if (category.Equals("MAIN"))
                    {
                        mainList.Add(dictionary);
                    }
                    if (category.Equals("DIV"))
                    {
                        divList.Add(dictionary);
                    }
                    if (category.Equals("GPS"))
                    {
                        gpsList.Add(dictionary);
                    }

                    row++;
                } while (true);

                //修改xml文件
                XmlDocument xmlDocument = new XmlDocument();
                XmlReaderSettings settings = new XmlReaderSettings();
                //忽略文档里的注释
                settings.IgnoreComments = true;
                XmlReader reader = XmlReader.Create(fileText.Text, settings);
                xmlDocument.Load(reader);
                reader.Close();
                //获取根节点-----CalibrationData
                XmlNode xmlNode = xmlDocument.SelectSingleNode("CalibrationData");
                //得到根节点的所有子节点-----CalConfig
                //XmlNodeList xmlNodeList = xmlNode.ChildNodes;
                XmlNodeList calConfigNodeList = xmlNode.SelectNodes("CalConfig");
                foreach (XmlNode calConfignode in calConfigNodeList)
                {
                    if (calConfignode.SelectSingleNode("CalPath") == null)
                    {
                        continue;
                    }

                    //将节点转换为元素,便于得到节点的属性值
                    XmlElement xmlElement = (XmlElement) calConfignode;
                    //得到CalConfig节点的name属性值
                    string calConfigName = xmlElement.GetAttribute("name");
                    if (calConfigName.Contains("DIV"))
                    {
                        if (divList.ToArray().Length > 0)
                            handleXml(calConfignode, divList);
                    }
                    else if (calConfigName.Contains("GPS") && gpsList.ToArray().Length > 0)
                    {
                        if (gpsList.ToArray().Length > 0)
                            handleXml(calConfignode, gpsList);
                    }
                    else
                    {
                        if (mainList.ToArray().Length > 0)
                            handleXml(calConfignode, mainList);
                    }
                }

                xmlDocument.Save(fileText.Text);
                Box.ShowInfoOk("恭喜你，加载BT线损成功！");
            }
            catch (Exception exception)
            {
                Box.ShowWarnOkCancel("很遗憾，加载BT线损失败！\r\n" + exception.Message);
            }
        }

        private void handleXml(XmlNode calConfignode,List<Dictionary<string, string>> list)
        {
            //得到CalConfig节点下的所有CalPath节点
            //XmlNodeList calPathNodes = calConfignode.ChildNodes;
            XmlNodeList calPathNodes = calConfignode.SelectNodes(@"CalPath");
            foreach (XmlNode calPathNode in calPathNodes)
            {
                //得到CalPath节点下的所有CalPoint节点
                //XmlNodeList calPointNodes = calPathNode.ChildNodes;
                XmlNodeList calPointNodes = calPathNode.SelectNodes(@"CalPoint");
                foreach (XmlNode calPointNode in calPointNodes)
                {
                    //将节点转换为元素,便于得到节点的属性值
                    XmlElement calPointElement = (XmlElement)calPointNode;
                    double freq = double.Parse(calPointElement.GetAttribute("freq"));
                    foreach (Dictionary<string, string> dictionary in list)
                    {
                        double freqStart = double.Parse(dictionary["freqStart"]);
                        double freqEnd = double.Parse(dictionary["freqEnd"]);
                        if ((freq > freqStart || freq.Equals(freqStart)) && (freq < freqEnd || freq.Equals(freqEnd)))
                        {
                            calPointElement.SetAttribute("loss", dictionary["loss"]);
                        }
                    }
                }
            }
        }

        //取消按钮点击事件
        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        //点击浏览按钮
        private void browseBtn_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "配置文件|*.xml";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                fileText.Text = openFileDialog.FileName;
            }
        }
    }
}
