﻿using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Dut.AtCommand.Property;
using AILinkFactoryAuto.Task;
using AILinkFactoryAuto.Task.Executer;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Dut.AtCommand.Executer
{
    public class AtCommandExecuter : IExecuter
    {
        private string pattern;

        private GlobalVaribles configGv;

        public AtCommandExecuter()
        {
            this.pattern = GlobalVaribles.PATTERN;
        }

        private string PreTranslateAtCommand(string atCommand)
        {
            string newAtCommand = atCommand;
            Match match = Regex.Match(atCommand, @"{([0-9a-zA-Z_]+)}");
            for (int i = 1; i < match.Groups.Count; i++)
            {
                string key = match.Groups[i].ToString();
                string value = configGv.Get(key);

                if (string.IsNullOrEmpty(value))
                {
                    throw new BaseException("null value in GlobalVaribles");
                }

                newAtCommand = newAtCommand.Replace("{" + key + "}", value);
            }

            return newAtCommand;
        }

        private string PreTranslateCheckInfo(string checkInfo)
        {
            string newCheckInfo = checkInfo;
            Match match = Regex.Match(checkInfo, pattern);
            for (int i = 1; i < match.Groups.Count; i++)
            {
                string key = match.Groups[i].ToString();
                newCheckInfo = configGv.Get(key);
            }

            return newCheckInfo;
        }

        private string Parse_r_n(string value)
        {
            value = value.Replace("\\r", "\r");
            value = value.Replace("\\R", "\r");
            value = value.Replace("\\n", "\n");
            value = value.Replace("\\N", "\n");
            return value;
        }

        public void Run(IProperties properties, GlobalDic<string, object> globalDic)
        {
            AtCommandProperties config = properties as AtCommandProperties;
            List<ComDut> comDutList = globalDic[typeof(List<ComDut>).ToString()] as List<ComDut>;
            //ComDut comDut = globalDic[typeof(ComDut).ToString()] as ComDut;
            ComDut comDut = null;
            foreach (var item in comDutList)
            {
                if (item.PortName == config.PortName)
                {
                    comDut = item;
                    break;
                }

            }
            if (comDut == null)
            {
                throw new BaseException(string.Format("ComDut No PortName:{0}", config.PortName));
            }



            //OpenPhoneProperties configOpenPhone = globalDic[typeof(OpenPhoneProperties).ToString()] as OpenPhoneProperties;
            List<OpenPhoneProperties> configList = globalDic[typeof(List<OpenPhoneProperties>).ToString()] as List<OpenPhoneProperties>;
            OpenPhoneProperties configOpenPhone = null;
            foreach (var item in configList)
            {
                if (item.PortName == config.PortName)
                {
                    configOpenPhone = item;
                    break;
                }

            }
            if (configOpenPhone == null)
            {
                throw new BaseException(string.Format("OpenPhoneProperties No PortName:{0}", config.PortName));
            }

            ILog log = globalDic[typeof(ILog).ToString()] as ILog;
            configGv = globalDic[typeof(GlobalVaribles).ToString()] as GlobalVaribles;

            comDut.Parity = configOpenPhone.Parity;
            string endLine = configOpenPhone.EndLine;
            if (!string.IsNullOrEmpty(endLine))
            {
                endLine = Parse_r_n(endLine);
            }
            if (config.CommandType == AtCommandProperties.EnumCommandType.String)
            {
                string atCommand = PreTranslateAtCommand(config.AtCommand);
                log.Info("AT Commond=" + atCommand);

                comDut.DtrEnable = configOpenPhone.Dtr;
                comDut.RtsEnable = configOpenPhone.Rts;
                comDut.Write(atCommand + endLine);

                Thread.Sleep(config.AtCommandInterval);
                string response = comDut.ReadExisting();
                comDut.DtrEnable = false;
                comDut.RtsEnable = false;

                log.Info("AT Response=" + response);

                if (!string.IsNullOrEmpty(config.AtCommandError))
                {
                    if (response.Contains(config.AtCommandError))
                    {
                        throw new BaseException(string.Format("AT response=[{0}] contain error=[{1}]", response, config.AtCommandError));
                    }
                }

                if (!string.IsNullOrEmpty(config.AtCommandOk))
                {
                    if (!response.Contains(config.AtCommandOk))
                    {
                        throw new BaseException(string.Format("AT response=[{0}] not contain error=[{1}]", response, config.AtCommandOk));
                    }
                }

                if (config.CheckInfo != null)
                {
                    for (int i = 0; i < config.CheckInfo.Length; i++)
                    {
                        if (!string.IsNullOrEmpty(config.CheckInfo[i]))
                        {
                            string checkInfo = PreTranslateCheckInfo(config.CheckInfo[i]);
                            if (!response.Contains(checkInfo))
                            {
                                throw new BaseException(string.Format("AT response=[{0}] not contain check info=[{1}]", response, checkInfo));
                            }
                        }
                    }
                }

                if (config.GlobalVariblesKey != null && config.GlobalVariblesKeyPattern != null)
                {
                    if (config.GlobalVariblesKey.Length != config.GlobalVariblesKeyPattern.Length)
                    {
                        throw new BaseException("请保持GlobalVariblesKey与GlobalVariblesKeyPattern成对存在");
                    }
                    for (int i = 0; i < config.GlobalVariblesKey.Length; i++)
                    {
                        string pattern = Parse_r_n(config.GlobalVariblesKeyPattern[i]);
                        Match matchValue = Regex.Match(response, pattern);
                        if (!matchValue.Success)
                        {
                            throw new BaseException("read info value fail");
                        }

                        string value = matchValue.Groups[1].ToString();

                        Match matchKey = Regex.Match(config.GlobalVariblesKey[i], this.pattern);
                        if (!matchKey.Success)
                        {
                            throw new BaseException("read info key fail");
                        }

                        string key = matchKey.Groups[1].ToString();

                        configGv.Add(key, value);
                    }
                }

            }
            else if (config.CommandType == AtCommandProperties.EnumCommandType.Hex)
            {
                byte[] atCommand = strToToHexByte(config.AtCommand);
                //string atCommand = PreTranslateAtCommand(config.AtCommand);
                log.Info("AT Commond=" + config.AtCommand);

                comDut.DtrEnable = configOpenPhone.Dtr;
                comDut.RtsEnable = configOpenPhone.Rts;
                comDut.Write(atCommand, 0, atCommand.Length);

                Thread.Sleep(config.AtCommandInterval);
                string response = comDut.ReadExisting();
                comDut.DtrEnable = false;
                comDut.RtsEnable = false;

                log.Info("AT Response=" + response);

                if (!string.IsNullOrEmpty(config.AtCommandError))
                {
                    if (response.Contains(config.AtCommandError))
                    {
                        throw new BaseException(string.Format("AT response=[{0}] contain error=[{1}]", response, config.AtCommandError));
                    }
                }

                if (!string.IsNullOrEmpty(config.AtCommandOk))
                {
                    if (!response.Contains(config.AtCommandOk))
                    {
                        throw new BaseException(string.Format("AT response=[{0}] not contain error=[{1}]", response, config.AtCommandOk));
                    }
                }

                if (config.CheckInfo != null)
                {
                    for (int i = 0; i < config.CheckInfo.Length; i++)
                    {
                        if (!string.IsNullOrEmpty(config.CheckInfo[i]))
                        {
                            string checkInfo = PreTranslateCheckInfo(config.CheckInfo[i]);
                            if (!response.Contains(checkInfo))
                            {
                                throw new BaseException(string.Format("AT response=[{0}] not contain check info=[{1}]", response, checkInfo));
                            }
                        }
                    }
                }

                if (config.GlobalVariblesKey != null && config.GlobalVariblesKeyPattern != null)
                {
                    if (config.GlobalVariblesKey.Length != config.GlobalVariblesKeyPattern.Length)
                    {
                        throw new BaseException("请保持GlobalVariblesKey与GlobalVariblesKeyPattern成对存在");
                    }
                    for (int i = 0; i < config.GlobalVariblesKey.Length; i++)
                    {
                        string pattern = "-([0-9]{2}) ";
                        Match matchValue = Regex.Match(response, pattern);
                        if (!matchValue.Success)
                        {
                            throw new BaseException("read info value fail");
                        }

                        string value = matchValue.Groups[1].ToString();

                        Match matchKey = Regex.Match(config.GlobalVariblesKey[i], this.pattern);
                        if (!matchKey.Success)
                        {
                            throw new BaseException("read info key fail");
                        }

                        string key = matchKey.Groups[1].ToString();

                        configGv.Add(key, value);
                    }
                }
            }
        }
        /// <summary>
        /// 字符串转16进制字节数组
        /// </summary>
        /// <param name="hexString"></param>
        /// <returns></returns>
        private static byte[] strToToHexByte(string hexString)
        {
            hexString = hexString.Replace(" ", "");
            if ((hexString.Length % 2) != 0)
                hexString += " ";
            byte[] returnBytes = new byte[hexString.Length / 2];
            for (int i = 0; i < returnBytes.Length; i++)
                returnBytes[i] = Convert.ToByte(hexString.Substring(i * 2, 2), 16);
            return returnBytes;
        }
    }
}
