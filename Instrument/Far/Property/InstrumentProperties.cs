using System.ComponentModel;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Instrument.Far.Property
{
    public enum InstrumentType
    {
        CMW500,
        CMW100
    }

    public class InstrumentProperties : CommonProperties
    {
        private string resource;

        private string logPath;

        private InstrumentType instrumentType;

        [Category("Common"), Description("instrument connect command")]
        public string Resource
        {
            get { return resource; }
            set { resource = value; }
        }

        [Category("Common"), Description("log's filename")]
        public string LogPath
        {
            get { return logPath; }
            set { logPath = value; }
        }

        [Category("Common"), Description("instrument type")]
        public InstrumentType InstrumentType
        {
            get { return instrumentType; }
            set { instrumentType = value; }
        }
    }
}
