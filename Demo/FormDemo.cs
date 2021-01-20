using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Windows.Forms;
using AILinkFactoryAuto.Instrument.WtApi;
using AILinkFactoryAuto.Task;
using AILinkFactoryAuto.Task.Property;
using AILinkFactoryAuto.Task.Wlan.Executer;
using AILinkFactoryAuto.Task.Wlan.Property;
using AILinkFactoryAuto.Task.Wlan.Utils;
using AILinkFactoryAuto.Utils;
using AILinkFactoryAuto.Wlan.Plugin;

namespace AILinkFactoryAuto.GenJts
{
    public partial class FormDemo : Form, IGenJts
    {
        public string ProjectPath { get; set; }

        public FormDemo()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            TaskItemManager taskItemManager = new TaskItemManager();

            if (true)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Connect Instument";
                taskItem.Executer = new ConnectInstrumentExecuter();
                taskItem.CommonProperties = new ConnectInstrumentProperties()
                {
                    ip = "192.168.10.253"
                };
                taskItemManager.Append(taskItem);
            }

            if (true)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Load Dll";
                taskItem.Executer = new LoadDllExecuter();
                Dictionary<string, KeyValue> wtSetUp = new Dictionary<string, KeyValue>();
                //wtSetUp.Add("WT_DUT_CONN_TYPE", new KeyValue()
                //{
                //    Key = "WT_DUT_CONN_TYPE",
                //    Value = "CARD",
                //    Descripiton = "DUT连接方式"
                //});
                //wtSetUp.Add("WT_DUT_CTRL_LIB_NAME", new KeyValue()
                //{
                //    Key = "WT_DUT_CTRL_LIB_NAME",
                //    Value = "MP_DLL.dll",
                //    Descripiton = "WT_DUT_CTRL_BT_LIB_NAME"
                //});
                //wtSetUp.Add("WT_DUT_CTRL_BT_LIB_NAME", new KeyValue()
                //{
                //    Key = "WT_DUT_CTRL_BT_LIB_NAME",
                //    Value = "RtlBluetoothMP.dll",
                //    Descripiton = "WT_DUT_CTRL_BT_LIB_NAME"
                //});
                //wtSetUp.Add("WT_OPEN_BT_BY_THREADS", new KeyValue()
                //{
                //    Key = "WT_OPEN_BT_BY_THREADS",
                //    Value = "1",
                //    Descripiton = "0:否 1:是"
                //});
                //wtSetUp.Add("WT_FORCE_TRUE_FOR_ISDUTREADY", new KeyValue()
                //{
                //    Key = "WT_FORCE_TRUE_FOR_ISDUTREADY",
                //    Value = "1",
                //    Descripiton = "若应用于机械手,可关闭此开关"
                //});
                //wtSetUp.Add("WT_DUT_ACK_TOKEN", new KeyValue()
                //{
                //    Key = "WT_DUT_ACK_TOKEN",
                //    Value = null,
                //    Descripiton = "WT_DUT_ACK_TOKEN"
                //});
                //wtSetUp.Add("WT_DISPLAY_TX_PACKET_NUMBER", new KeyValue()
                //{
                //    Key = "WT_DISPLAY_TX_PACKET_NUMBER",
                //    Value = "0",
                //    Descripiton = "是否打印TX发包情况"
                //});
                //wtSetUp.Add("WT_DUT_HAS_11AC", new KeyValue()
                //{
                //    Key = "WT_DUT_HAS_11AC",
                //    Value = "0",
                //    Descripiton = "DUT是否支持11AC"
                //});
                //wtSetUp.Add("WT_DUT_BAND_2G", new KeyValue()
                //{
                //    Key = "WT_DUT_BAND_2G",
                //    Value = "1",
                //    Descripiton = "DUT是否支持2.4G"
                //});
                //wtSetUp.Add("WT_DUT_BAND_5G", new KeyValue()
                //{
                //    Key = "WT_DUT_BAND_5G",
                //    Value = "0",
                //    Descripiton = "DUT是否支持5.8G"
                //});
                //wtSetUp.Add("WT_DUT_ANT_2G", new KeyValue()
                //{
                //    Key = "WT_DUT_ANT_2G",
                //    Value = "2",
                //    Descripiton = "DUT 2.4G天线数目"
                //});
                //wtSetUp.Add("WT_DUT_ANT_5G", new KeyValue()
                //{
                //    Key = "WT_DUT_ANT_5G",
                //    Value = "2",
                //    Descripiton = "DUT 5G天线数目"
                //});
                //wtSetUp.Add("WT_DUT_IF_2G", new KeyValue()
                //{
                //    Key = "WT_DUT_IF_2G",
                //    Value = null,
                //    Descripiton = "WT_DUT_IF_2G"
                //});
                //wtSetUp.Add("WT_POWER_CAL_TXGAINK_UP_BT", new KeyValue()
                //{
                //    Key = "WT_POWER_CAL_TXGAINK_UP_BT",
                //    Value = null,
                //    Descripiton = "WT_POWER_CAL_TXGAINK_UP_BT"
                //});
                //wtSetUp.Add("WT_POWER_CAL_TXGAINK_LOW_BT", new KeyValue()
                //{
                //    Key = "WT_POWER_CAL_TXGAINK_LOW_BT",
                //    Value = null,
                //    Descripiton = "WT_POWER_CAL_TXGAINK_LOW_BT"
                //});
                //wtSetUp.Add("WT_FREQ_CAL_DEFAULT_REG", new KeyValue()
                //{
                //    Key = "WT_FREQ_CAL_DEFAULT_REG",
                //    Value = "0",
                //    Descripiton = "频偏寄存器值默认值"
                //});
                //wtSetUp.Add("WT_FREQ_CAL_DEFAULT_REG_5G", new KeyValue()
                //{
                //    Key = "WT_FREQ_CAL_DEFAULT_REG_5G",
                //    Value = "0",
                //    Descripiton = "5G频偏寄存器值默认值"
                //});
                //wtSetUp.Add("WT_DUT_FREQ_REG_RANGE", new KeyValue()
                //{
                //    Key = "WT_DUT_FREQ_REG_RANGE",
                //    Value = "0 127",
                //    Descripiton = "DUT频偏寄存器范围 MIN MAX"
                //});
                //wtSetUp.Add("WT_DUT_POWER_REG_RANGE", new KeyValue()
                //{
                //    Key = "WT_DUT_POWER_REG_RANGE",
                //    Value = "0 127",
                //    Descripiton = "DUT功率寄存器范围 MIN MAX"
                //});
                //wtSetUp.Add("WT_POWER_REG_RANGE_2_4G", new KeyValue()
                //{
                //    Key = "WT_POWER_REG_RANGE_2_4G",
                //    Value = "0 63 0 63 0 63 0 63 0 63",
                //    Descripiton = "Min_11B	Max_11B	Min_11G	Max_11G	Min_N20	Max_N20	Min_N40	Max_N40	Min_AC80 Max_AC80"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_11B", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_11B",
                //    Value = "17",
                //    Descripiton = "11B目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_OFDM_2_4G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_OFDM_2_4G",
                //    Value = "15",
                //    Descripiton = "2.4G 11g 54M目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_HT20_2_4G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_HT20_2_4G",
                //    Value = "14",
                //    Descripiton = "2.4G HT20目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_HT40_2_4G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_HT40_2_4G",
                //    Value = "14",
                //    Descripiton = "2.4G HT40目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_AC20_2_4G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_AC20_2_4G",
                //    Value = "14",
                //    Descripiton = "2.4G AC20目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_AC40_2_4G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_AC40_2_4G",
                //    Value = "14",
                //    Descripiton = "2.4G AC40目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_AC80_2_4G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_AC80_2_4G",
                //    Value = "14",
                //    Descripiton = "2.4G AC80目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_OFDM_5G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_OFDM_5G",
                //    Value = "15",
                //    Descripiton = "5G 11g 54M目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_HT20_5G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_HT20_5G",
                //    Value = "15",
                //    Descripiton = "5G HT20目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_HT40_5G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_HT40_5G",
                //    Value = "15",
                //    Descripiton = "5G HT40目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_AC20_5G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_AC20_5G",
                //    Value = "15",
                //    Descripiton = "5G AC20目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_AC40_5G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_AC40_5G",
                //    Value = "15",
                //    Descripiton = "5G AC40目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_AC80_5G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_AC80_5G",
                //    Value = "15",
                //    Descripiton = "5G AC80目标功率，dBm，取值范围(-100-100)"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_LEGACY_RATE_DIFF_2_4G", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_LEGACY_RATE_DIFF_2_4G",
                //    Value = null,
                //    Descripiton = "WT_TARGET_PWR_LEGACY_RATE_DIFF_2_4G"
                //});
                //wtSetUp.Add("WT_TARGET_PWR_LEGACY_RATE_DIFF", new KeyValue()
                //{
                //    Key = "WT_TARGET_PWR_LEGACY_RATE_DIFF",
                //    Value = "0 0 0 0 0 0 0 0 0 0 0 0",
                //    Descripiton = "54M 48M 36M 24M 18M 12M 9M 6M 11M 5.5M 2M 1M"
                //});
                //wtSetUp.Add("WT_POW_CAL_DEFAULT_REG_11B_CH0", new KeyValue()
                //{
                //    Key = "WT_POW_CAL_DEFAULT_REG_11B_CH0",
                //    Value = "45 45 45 45 45 45",
                //    Descripiton = "功率寄存器值默认值 Channel [1-2] [3-5] [6-8] [9-11] [12-13] [14]"
                //});
                //wtSetUp.Add("WT_POW_CAL_DEFAULT_REG_11B_CH1", new KeyValue()
                //{
                //    Key = "WT_POW_CAL_DEFAULT_REG_11B_CH1",
                //    Value = "45 45 45 45 45 45",
                //    Descripiton = "功率寄存器值默认值 Channel [1-2] [3-5] [6-8] [9-11] [12-13] [14]"
                //});
                //wtSetUp.Add("WT_POW_CAL_DEFAULT_REG_2_4G_HT40_CH0", new KeyValue()
                //{
                //    Key = "WT_POW_CAL_DEFAULT_REG_2_4G_HT40_CH0",
                //    Value = "49 49 0 49 49",
                //    Descripiton = "功率寄存器值默认值 Channel [1-2] [3-5] [6-8] [9-11] [12-14]"
                //});
                //wtSetUp.Add("WT_POW_CAL_DEFAULT_REG_2_4G_HT40_CH1", new KeyValue()
                //{
                //    Key = "WT_POW_CAL_DEFAULT_REG_2_4G_HT40_CH1",
                //    Value = "49 49 49 49 49",
                //    Descripiton = "功率寄存器值默认值 Channel [1-2] [3-5] [6-8] [9-11] [12-14]"
                //});
                //wtSetUp.Add("WT_POW_CAL_DEFAULT_REG_5GL_HT40_CH0", new KeyValue()
                //{
                //    Key = "WT_POW_CAL_DEFAULT_REG_5GL_HT40_CH0",
                //    Value = "0 0 0 0",
                //    Descripiton = "功率寄存器值默认值 Channel [36-42] [44-48] [52-58] [60-64]"
                //});
                //wtSetUp.Add("WT_POW_CAL_DEFAULT_REG_5GL_HT40_CH1", new KeyValue()
                //{
                //    Key = "WT_POW_CAL_DEFAULT_REG_5GL_HT40_CH1",
                //    Value = "0 0 0 0",
                //    Descripiton = "功率寄存器值默认值 Channel [36-42] [44-48] [52-58] [60-64]"
                //});
                //wtSetUp.Add("WT_POW_CAL_DEFAULT_REG_5GM_HT40_CH0", new KeyValue()
                //{
                //    Key = "WT_POW_CAL_DEFAULT_REG_5GM_HT40_CH0",
                //    Value = "0 80 80 80	80 67",
                //    Descripiton = "功率寄存器值默认值 Channel [100-106] [108-112] [116-122]	[124-128] [132-138] [140-144]]"
                //});
                //wtSetUp.Add("WT_POW_CAL_DEFAULT_REG_5GM_HT40_CH1", new KeyValue()
                //{
                //    Key = "WT_POW_CAL_DEFAULT_REG_5GM_HT40_CH1",
                //    Value = "0 80 80 80	80 0",
                //    Descripiton = "功率寄存器值默认值 Channel [100-106] [108-112] [116-122]	[124-128] [132-138] [140-144]]"
                //});
                //wtSetUp.Add("WT_POW_CAL_DEFAULT_REG_5GH_HT40_CH0", new KeyValue()
                //{
                //    Key = "WT_POW_CAL_DEFAULT_REG_5GH_HT40_CH0",
                //    Value = "64 80 80 62 ",
                //    Descripiton = "功率寄存器值默认值 Channel [149-155] [157-161] [165-171]	[173-177]"
                //});
                //wtSetUp.Add("WT_POW_CAL_DEFAULT_REG_5GH_HT40_CH1", new KeyValue()
                //{
                //    Key = "WT_POW_CAL_DEFAULT_REG_5GH_HT40_CH1",
                //    Value = "0 80 80 0",
                //    Descripiton = "功率寄存器值默认值 Channel [149-155] [157-161] [165-171]	[173-177]"
                //});
                //wtSetUp.Add("WT_TOTAL_EFUSE_NUMBER_OF_NEWDUT", new KeyValue()
                //{
                //    Key = "WT_TOTAL_EFUSE_NUMBER_OF_NEWDUT",
                //    Value = "512",
                //    Descripiton = "未进行烧写DUT总EFUSE个数,重新插拔DUT后生效"
                //});
                //wtSetUp.Add("WT_SWITCH_TX_PWR_TRACKING", new KeyValue()
                //{
                //    Key = "WT_SWITCH_TX_PWR_TRACKING",
                //    Value = "9",
                //    Descripiton = "//以bit位组合形式决定执行TxPwrTrack的方式\r\n" +
                //                  "1:在打开Dut时执行关闭TxPwrTrack功能\r\n" +
                //                  "2:在打开Dut时执行开启TxPwrTrack功能\r\n" +
                //                  "4:在CalEnd时执行关闭TxPwrTrack功能\r\n" +
                //                  "8:在CalEnd时执行开启TxPwrTrack功能"
                //});
                //wtSetUp.Add("WT_TX_VERIFY_FREQ_GAINVALUE_SOURCE", new KeyValue()
                //{
                //    Key = "WT_TX_VERIFY_FREQ_GAINVALUE_SOURCE",
                //    Value = "1",
                //    Descripiton = "Verify时频偏因子值（同时也写入DUT的efuse）的来源(不进行频偏校准时有效)\r\n" +
                //                  "1：频偏因子值使用Map文件里的值\r\n" +
                //                  "2：频偏因子值使用efuse的值"
                //});
                //wtSetUp.Add("WT_TX_VERIFY_PWR_GAINVALUE_SOURCE", new KeyValue()
                //{
                //    Key = "WT_TX_VERIFY_PWR_GAINVALUE_SOURCE",
                //    Value = "1",
                //    Descripiton = "Verify时功率因子值（同时也写入DUT的efuse）的来源(不进行频偏校准时有效)\r\n" +
                //                  "1：频偏因子值使用Map文件里的值\r\n" +
                //                  "2：频偏因子值使用efuse的值"
                //});
                //wtSetUp.Add("WT_TX_VERIFY_THERMAL_VALUE_SOURCE", new KeyValue()
                //{
                //    Key = "WT_TX_VERIFY_THERMAL_VALUE_SOURCE",
                //    Value = "1",
                //    Descripiton = "温补值（同时也写入DUT的efuse）的来源(不进行频偏校准时有效)\r\n" +
                //                  "1：频偏因子值使用Map文件里的值\r\n" +
                //                  "2：频偏因子值使用efuse的值"
                //});

                taskItem.CommonProperties = new LoadDllProperties()
                {
                    //Filename = "MT3620.DLL"
                    //Filename = "DutCtrl_RTL8723BU.DLL",
                    Filename = "RTL8822CU.DLL",
                    InfoType = InfoType.WLAN_TESER,
                    Sequence = 1,
                    WtSetUp = wtSetUp,
                    RetryCount = 0
                };
                taskItemManager.Append(taskItem);
            }

            if (false)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Is Dut Ready";
                taskItem.Executer = new IsDutReadyExecuter();
                taskItem.CommonProperties = new IsDutReadyProperties();
                taskItemManager.Append(taskItem);
            }

            if (true)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Dut Init";
                taskItem.Executer = new DutInitExecuter();
                taskItem.CommonProperties = new DutInitProperties();
                taskItemManager.Append(taskItem);
            }

            if (true)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Open Dut";
                taskItem.Executer = new OpenDutExecuter();
                taskItem.CommonProperties = new OpenDutProperties()
                {
                    RetryCount = 0
                };
                taskItemManager.Append(taskItem);
            }

            bool txVerfiy = false;

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Cal Begin";
                taskItem.Executer = new CalBeginExecuter();
                taskItem.CommonProperties = new CalBeginProperties();
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "FreqCal 54M 2442";
                taskItem.Executer = new FreqCalExecuter();
                taskItem.CommonProperties = new CalProperties()
                {
                    Power = 15,
                    Freq = 2442,
                    Demod = WtDemo.WT_DEMOD_11AG,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS_54M,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_20M,
                    Loss = 4.3,
                    DelayCal = 100,
                    LimitMin = -2,
                    LimitMax = 2,
                    RetryCountCal = 10,
                    RetryCount = 0
                };
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "PowerCal 11M 2442";
                taskItem.Executer = new PowerCalExecuter();
                taskItem.CommonProperties = new CalProperties()
                {
                    Power = 17,
                    Freq = 2442,
                    Demod = WtDemo.WT_DEMOD_11B,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS_11M,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_20M,
                    Loss = 4.3,
                    DelayCal = 50,
                    LimitMin = -0.5,
                    LimitMax = 0.5,
                    RetryCountCal = 10,
                    RetryCount = 0
                };
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "PowerCal HT40 2437";
                taskItem.Executer = new PowerCalExecuter();
                taskItem.CommonProperties = new CalProperties()
                {
                    Power = 15,
                    Freq = 2437,
                    Demod = WtDemo.WT_DEMOD_11N_40M,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS7,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_40M,
                    Loss = 4.4,
                    DelayCal = 50,
                    LimitMin = -0.5,
                    LimitMax = 0.5,
                    RetryCountCal = 10,
                    RetryCount = 0
                };
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "PowerCal HT40 5190";
                taskItem.Executer = new PowerCalExecuter();
                taskItem.CommonProperties = new CalProperties()
                {
                    Power = 15,
                    Freq = 5190,
                    Demod = WtDemo.WT_DEMOD_11N_40M,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS7,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_40M,
                    Loss = 5.8,
                    DelayCal = 50,
                    LimitMin = -0.5,
                    LimitMax = 0.5,
                    RetryCountCal = 10,
                    RetryCount = 0
                };
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "PowerCal HT40 5510";
                taskItem.Executer = new PowerCalExecuter();
                taskItem.CommonProperties = new CalProperties()
                {
                    Power = 15,
                    Freq = 5510,
                    Demod = WtDemo.WT_DEMOD_11N_40M,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS7,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_40M,
                    Loss = 5.6,
                    DelayCal = 50,
                    LimitMin = -0.5,
                    LimitMax = 0.5,
                    RetryCountCal = 10,
                    RetryCount = 0
                };
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "PowerCal HT40 5755";
                taskItem.Executer = new PowerCalExecuter();
                taskItem.CommonProperties = new CalProperties()
                {
                    Power = 15,
                    Freq = 5755,
                    Demod = WtDemo.WT_DEMOD_11N_40M,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS7,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_40M,
                    Loss = 5.9,
                    DelayCal = 50,
                    LimitMin = -0.5,
                    LimitMax = 0.5,
                    RetryCountCal = 10,
                    RetryCount = 0
                };
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Cal End";
                taskItem.Executer = new CalEndExecuter();
                taskItem.CommonProperties = new CalEndProperties();
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "TxVerify 11M 2472";
                taskItem.Executer = new TxVerifyWifiExecuter();
                TxVerifyWifiProperties config = new TxVerifyWifiProperties()
                {
                    Power = 17,
                    Freq = 2472,
                    Demod = WtDemo.WT_DEMOD_11B,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS_11M,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_20M,
                    Loss = 4.4
                };

                config.LimitPower.Lower = "15.5";
                config.LimitPower.Upper = "18.5";

                config.LimitEvm.Lower = "-45";
                config.LimitEvm.Upper = "-10";

                config.LimitFreqErr.Lower = "-10";
                config.LimitFreqErr.Upper = "10";

                config.LimitMaskErr.Lower = "0";
                config.LimitMaskErr.Upper = "5.12";

                taskItem.CommonProperties = config;
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "TxVerify 54M 2412";
                taskItem.Executer = new TxVerifyWifiExecuter();
                TxVerifyWifiProperties config = new TxVerifyWifiProperties()
                {
                    Power = 17,
                    Freq = 2412,
                    Demod = WtDemo.WT_DEMOD_11AG,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS_54M,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_20M,
                    Loss = 4.0
                };

                config.LimitPower.Lower = "13.5";
                config.LimitPower.Upper = "16.5";

                config.LimitEvm.Lower = "-45";
                config.LimitEvm.Upper = "-20";

                config.LimitFreqErr.Lower = "-10";
                config.LimitFreqErr.Upper = "10";

                config.LimitMaskErr.Lower = "0";
                config.LimitMaskErr.Upper = "5.12";

                taskItem.CommonProperties = config;
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "TxVerify HT20 2442";
                taskItem.Executer = new TxVerifyWifiExecuter();
                TxVerifyWifiProperties config = new TxVerifyWifiProperties()
                {
                    Power = 17,
                    Freq = 2442,
                    Demod = WtDemo.WT_DEMOD_11N_20M,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS7,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_20M,
                    Loss = 4.3
                };

                config.LimitPower.Lower = "13.5";
                config.LimitPower.Upper = "16.5";

                config.LimitEvm.Lower = "-45";
                config.LimitEvm.Upper = "-27";

                config.LimitFreqErr.Lower = "-10";
                config.LimitFreqErr.Upper = "10";

                config.LimitMaskErr.Lower = "0";
                config.LimitMaskErr.Upper = "5.12";

                taskItem.CommonProperties = config;
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "TxVerify HT40 5530";
                taskItem.Executer = new TxVerifyWifiExecuter();
                TxVerifyWifiProperties config = new TxVerifyWifiProperties()
                {
                    Power = 14,
                    Freq = 5530,
                    Demod = WtDemo.WT_DEMOD_11N_40M,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS7,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_40M,
                    Loss = 5.8
                };

                config.LimitPower.Lower = "13.5";
                config.LimitPower.Upper = "16.5";

                config.LimitEvm.Lower = "-45";
                config.LimitEvm.Upper = "-27";

                config.LimitFreqErr.Lower = "-10";
                config.LimitFreqErr.Upper = "10";

                config.LimitMaskErr.Lower = "0";
                config.LimitMaskErr.Upper = "5.12";

                taskItem.CommonProperties = config;
                taskItemManager.Append(taskItem);
            }

            if (txVerfiy)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "TxVerify AC80 5755";
                taskItem.Executer = new TxVerifyWifiExecuter();
                TxVerifyWifiProperties config = new TxVerifyWifiProperties()
                {
                    Power = 14,
                    Freq = 5755,
                    Demod = WtDemo.WT_DEMOD_11AC_80M,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS9,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_80M,
                    Loss = 5.9
                };

                config.LimitPower.Lower = "13.5";
                config.LimitPower.Upper = "16.5";

                config.LimitEvm.Lower = "-45";
                config.LimitEvm.Upper = "-32";

                config.LimitFreqErr.Lower = "-10";
                config.LimitFreqErr.Upper = "10";

                config.LimitMaskErr.Lower = "0";
                config.LimitMaskErr.Upper = "5.12";

                taskItem.CommonProperties = config;
                taskItemManager.Append(taskItem);
            }

            if (true)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "RxVerify HT20 2442";
                taskItem.Executer = new RxVerifyWifiExecuter();
                RxVerifyWifiProperties config = new RxVerifyWifiProperties()
                {
                    Power = -40,
                    Freq = 2442,
                    Demod = WtDemo.WT_DEMOD_11N_20M,
                    Antenna = WtChain.CHAIN0,
                    WtMcs = WtMcs.MCS7,
                    Port = WtPort.WT_PORT_RF4,
                    WtBw = WtBw.eumBw_20M,
                    Loss = 5.9,
                    NumberPackets = 1000
                };
                config.LimitNumberPackets.Lower = "980";
                taskItem.CommonProperties = config;
                taskItemManager.Append(taskItem);
            }

            if (false)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Set Mac";
                taskItem.Executer = new SetMacAddressExecuter();
                taskItem.CommonProperties = new CommonProperties();
                taskItemManager.Append(taskItem);
            }

            if (false)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Save Cal Data";
                taskItem.Executer = new SaveCalDataExecuter();
                taskItem.CommonProperties = new CommonProperties();
                taskItemManager.Append(taskItem);
            }

            if (false)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Write Efuse";
                taskItem.Executer = new WriteEfuseExecuter();
                taskItem.CommonProperties = new WriteEfuseProperties()
                {
                    WtDut = WtDut.WT_DUT_WIFI_2G
                };
                taskItemManager.Append(taskItem);
            }

            if (true)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Close Dut";
                taskItem.Executer = new CloseDutExecuter();
                taskItem.CommonProperties = new CloseDutProperties();
                taskItemManager.Append(taskItem);
            }

            if (true)
            {
                TaskItem taskItem = new TaskItem();
                taskItem.Enable = true;
                taskItem.Item = "Disconnect Instument";
                taskItem.Executer = new DisconnectInstrumentExecuter();
                taskItem.CommonProperties = new DisconnectInstrumentProperties()
                {
                    RetryCount = 0,
                    ExecuteCondition = ExecuteCondition.ALWAYS
                };
                taskItemManager.Append(taskItem);
            }

            taskItemManager.Save2Jts(this, 1, "demo");

            this.Close();
        }
    }
}
