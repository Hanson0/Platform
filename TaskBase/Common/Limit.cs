using System;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.Common
{
    public class Limit
    {
        private ILog log;

        public Limit(ILog log)
        {
            this.log = log;
        }

        //public ILog Log
        //{
        //    set { log = value; }
        //}

        //public static void lowerShow(bool state,string name)
        //{
        //    string info;
        //    if (state)
        //    {
        //        info = string.Format("{0} : {1}", name, "PASS");
        //        log.Pass(info);
        //    }
        //    else
        //    {
        //        info = string.Format("{0} : {1}", name, "FAIL");
        //        log.Fail(info);
        //    }
        //}

        public bool CheckDouble(double value, LimitProperties limitProperties)
        {
            return CheckString(value.ToString(), limitProperties);
        }

        public bool CheckString(string value, LimitProperties limitProperties)
        {
            if (!limitProperties.Enable)
            {
                return true;
            }

            bool result = false;
            string info;
            try
            {
                double _value = Convert.ToDouble(value);
                if (!double.IsNaN(_value))
                {
                    result = Check(_value, limitProperties);
                }
                info = string.Format("{0}={1}{2},[{3},{4}]", limitProperties.Name, _value, limitProperties.Unit, limitProperties.Lower,
                    limitProperties.Upper);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                if (string.IsNullOrEmpty(limitProperties.Lower) && 
                    string.IsNullOrEmpty(limitProperties.Upper))
                {
                    result = true;
                }
                info = string.Format("{0}={1}{2},[{3},{4}]", limitProperties.Name, value, limitProperties.Unit, limitProperties.Lower,
                    limitProperties.Upper);
            }

            if (result)
            {
                log.Pass(info);
            }
            else
            {
                log.Fail(info);
            }

            return result;
        }

        private bool Check(double value, LimitProperties limitProperties)
        {
            bool result = true;
            if (!string.IsNullOrEmpty(limitProperties.Lower))
            {
                double lower = Convert.ToDouble(limitProperties.Lower);
                if (value < lower)
                {
                    result = false;
                    return result;
                }
            }

            if (!string.IsNullOrEmpty(limitProperties.Upper))
            {
                double upper = Convert.ToDouble(limitProperties.Upper);
                if (value > upper)
                {
                    result = false;
                    return result;
                }
            }

            return result;
        }
    }
}
