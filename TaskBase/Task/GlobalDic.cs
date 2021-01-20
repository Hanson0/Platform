using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Utils;

namespace AILinkFactoryAuto.Task
{
    public class GlobalDic<TKey, TValue> : Dictionary<TKey, TValue> where TKey : class
    {
        /// <summary>
        /// 按键值对保存
        /// 键：typeof(interface).toString()
        /// 值：value
        /// 如果希望Tkey为typeof(interface).toString()
        /// 此函数不支持
        /// 请使用public void Put<T>(TValue value) where T : class
        /// </summary>
        /// <param name="value">值</param>
        public void Put(TValue value)
        {
            string keyString = value.GetType().ToString();
            TKey key = keyString as TKey;
            if (key == null)
            {
                throw new Exception("TKey is null");
            }

            if (typeof(TKey) == typeof(string))
            {            
                this.Add(key, value);
            }
            else
            {
                throw new Exception("TKey只支持string");
            }
        }

        /// <summary>
        /// 按键值对保存
        /// 键：typeof(T).toString()
        /// 值：value
        /// </summary>
        /// <typeparam name="T">键：typeof(T).toString()</typeparam>
        /// <param name="value">值</param>
        public void Put<T>(TValue value) where T : class
        {
            string keyString = typeof(T).ToString();
            TKey tKey = keyString as TKey;
            if (tKey == null)
            {
                throw new Exception("TKey is null");
            }

            if (typeof(TKey) == typeof(string))
            {
                this.Add(tKey, value);
            }
            else
            {
                throw new Exception("TKey只支持string");
            }
        }

        /// <summary>
        /// 根据键：typeof(T).toString()获取值
        /// </summary>
        /// <typeparam name="T">键：typeof(T).toString()</typeparam>
        /// <returns>值：typeof(T)</returns>
        public T Get<T>() where T : class
        {
            string keyString = typeof(T).ToString();
            TKey key = keyString as TKey;
            if (key == null)
            {
                throw new Exception("TKey is null");
            }

            if (typeof(TKey) == typeof(string))
            {
                try
                {
                    return this[key] as T;
                }
                catch (Exception e)
                {
                    LogUtils.UiDebug.Debug(e.ToString());
                    return null;
                }
  
            }

            throw new Exception("TKey只支持string");
        }
    }
}
