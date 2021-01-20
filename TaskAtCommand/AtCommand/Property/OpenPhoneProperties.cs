using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.Dut.AtCommand.Property.Converter;
using System.IO.Ports;

namespace AILinkFactoryAuto.Dut.AtCommand.Property
{
    public enum AtType
    {
        Manual,
        Auto
    }

    public class OpenPhoneProperties : CommonProperties
    {
        private string portName;

        private int baudRate;

        private bool rts;

        private bool dtr;

        private string endLine;

        private AtType atType;

        private Parity parity;

        private string[] autoKey;

        private int sleepTimeAfterFindDut;

        [Category("Common"), Description("at type")]
        public AtType AtType
        {
            get { return atType; }
            set { atType = value; }
        }

        [Category("Common"), Description("sleep time after find dut")]
        public int SleepTimeAfterFindDut
        {
            get { return sleepTimeAfterFindDut; }
            set { sleepTimeAfterFindDut = value; }
        }

        [Category("SerialPort"), Description("PortName"), TypeConverter(typeof(PortNamesConverter))]
        public string PortName
        {
            get { return portName; }
            set { portName = value; }
        }

        [Category("SerialPort"), Description("BaudRate")]
        public int BaudRate
        {
            get { return baudRate; }
            set { baudRate = value; }
        }

        [Category("SerialPort"), Description("数据终端就绪 (RTS) 信号")]
        public bool Rts
        {
            get { return rts; }
            set { rts = value; }
        }

        [Category("SerialPort"), Description("数据终端就绪 (DTR) 信号")]
        public bool Dtr
        {
            get { return dtr; }
            set { dtr = value; }
        }

        [Category("SerialPort"), Description("Parity 奇偶校验位")]
        public Parity Parity
        {
            get { return parity; }
            set { parity = value; }
        }
        

        [Category("SerialPort"), Description("AT Command 结束符")]
        public string EndLine
        {
            get { return endLine; }
            set { endLine = value; }
        }

        [Category("SerialPort"), Description("自动查找的关键字符串")]
        public string[] AutoKey
        {
            get { return autoKey; }
            set { autoKey = value; }
        }
    }
}
