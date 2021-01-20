using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;

namespace AILinkFactoryAuto.Task.Property
{
    public class PrintLabelProperties : CommonProperties
    {

        /// <summary>
        /// BarTender应用程序文件
        /// </summary>
        private string _bartenderFile;

        /// <summary>
        /// BarTender模板文件
        /// </summary>
        private string _tempalteFile;

        /// <summary>
        /// 打印数据文件
        /// </summary>
        private string _dataFile;



        /// <summary>
        /// 数据头部
        /// </summary>
        private string dataHead;

        //private PrintLabelProperties()
        //{
        //    BartenderFile = @"C:\Program Files (x86)\Seagull\BarTender\8.0\bartend.exe",
        //    TempalteFile = @"E:\手环IMEI打印测试模板.btw",
        //    DataFile = @"D:\DataMac.txt",
        //    DataHead = "IMEI,SN,ICCID,IMSI,MAC",
        //}



        //字段
        [Category("Bartender"), Description("BarTender应用程序文件")]
        public string BartenderFile
        {
            get 
            {
                if (string.IsNullOrEmpty(_bartenderFile))
                {
                    _bartenderFile = @"C:\Program Files (x86)\Seagull\BarTender\8.0\bartend.exe";
                }
                return _bartenderFile; 
            }
            set { _bartenderFile = value; }
        }
        [Category("Bartender"), Description("BarTender模板文件,如:E:\\模板.btw")]
        public string TempalteFile
        {
            get { return _tempalteFile; }

            set { _tempalteFile = value; }
        }
        [Category("Bartender"), Description("打印数据库文件")]
        public string DataFile
        {

            get
            {
                if (string.IsNullOrEmpty(_dataFile))
                {
                    _dataFile = "D:\\DataFile.txt";
                }
                return _dataFile;
            }
            set { _dataFile = value; }
        }
        [Category("Bartender"), Description("数据头")]

        public string DataHead
        {
            get 
            {
                if (string.IsNullOrEmpty(dataHead))
                {
                    dataHead = "IMEI,SN,ICCID,IMSI,MAC";
                }
                return dataHead;
            }
            set { dataHead = value; }
        }


    }
}
