using System;
using System.IO;
using System.Text;

namespace AILinkFactoryAuto.Utils
{
    public class WtInfoUtils
    {
        public static int WriteProfileString(string lpKeyName, string lpString, string lpFileName)
        {
            int ret = -1;

            if (string.IsNullOrEmpty(lpKeyName) || string.IsNullOrEmpty(lpString))
            {
                return ret;
            }

            try
            {
                string[] strContent = File.ReadAllLines(lpFileName, Encoding.Default);

                for (int i = 0; i < strContent.Length; i++)
                {
                    int index = -1;
                    string strValid = null;
                    index = strContent[i].IndexOf("//");
                    if (index == 0)
                    {
                        continue;
                    }
                    else if (index > 0)
                    {
                        strValid = strContent[i].Substring(0, index);
                    }
                    else
                    {
                        strValid = strContent[i];
                    }

                    if (string.IsNullOrEmpty(strValid))
                    {
                        continue;
                    }

                    index = strValid.IndexOf("=");

                    if (index < 0)
                    {
                        continue;
                    }

                    StringBuilder strKeyName = new StringBuilder(strValid.Substring(0, index));
                    strKeyName.Replace("\t", "");
                    strKeyName.Replace(" ", "");
                    if (strKeyName.ToString() == lpKeyName)
                    {
                        index = index + 1;

                        string strHead = strValid.Substring(0, index);
                        string strEnd = strValid.Substring(index, strValid.Length - index);
                        bool findData = false;
                        foreach (char charItem in strEnd)
                        {
                            if (charItem == ' ' || charItem == '\t')
                            {
                                strHead = strHead + charItem.ToString();
                            }
                            else
                            {
                                if (!findData)
                                {
                                    findData = true;
                                    strHead += lpString;
                                }
                                continue;
                            }
                        }

                        if (!findData)
                        {
                            findData = true;
                            strHead += lpString;
                        }

                        index = strContent[i].IndexOf("//");
                        if (index > 0)
                        {
                            strHead += strContent[i].Substring(index, strContent[i].Length - index);
                        }

                        if (findData)
                        {
                            strContent[i] = strHead;
                        }

                        File.WriteAllLines(lpFileName, strContent, Encoding.Default);
                        ret = 0;
                        break;
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

            return ret;
        }

        public static int ReadProfileString(string lpKeyName, ref string lpReturnedString, string lpFileName)
        {
            int ret = -1;

            if (string.IsNullOrEmpty(lpKeyName))
            {
                return ret;
            }

            try
            {
                string[] strContent = File.ReadAllLines(lpFileName, Encoding.Default);

                for (int i = 0; i < strContent.Length; i++)
                {
                    int index = -1;
                    string strValid = null;
                    index = strContent[i].IndexOf("//");
                    if (index == 0)
                    {
                        continue;
                    }
                    else if (index > 0)
                    {
                        strValid = strContent[i].Substring(0, index);
                    }
                    else
                    {
                        strValid = strContent[i];
                    }

                    if (string.IsNullOrEmpty(strValid))
                    {
                        continue;
                    }

                    //index = strValid.IndexOf("=");

                    //if (index < 0)
                    //{
                    //    continue;
                    //}

                    string[] separator = new string[3] { "=", " ", "\t" };
                    string[] strLineList = strValid.Split(separator, StringSplitOptions.RemoveEmptyEntries);

                    if (strLineList.Length >= 2)
                    {
                        if (strLineList[0] == lpKeyName)
                        {
                            for (int j = 1; j < strLineList.Length; j++)
                            {
                                if (j == 1)
                                {
                                    lpReturnedString += strLineList[j];
                                }
                                else
                                {
                                    lpReturnedString += " " + strLineList[j];
                                }
                            }

                            ret = 0;
                            break;
                        }
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

            return ret;
        }
    }
}