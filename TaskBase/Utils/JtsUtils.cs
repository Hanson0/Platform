using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using AILinkFactoryAuto.Core;
using AILinkFactoryAuto.Task;
using Newtonsoft.Json;

namespace AILinkFactoryAuto.Utils
{
    public class JtsUtils
    {
        private static JsonTestSequence jsonTestSequence = new JsonTestSequence();

        public static void SaveJsonFile(string jsonFile, List<TaskItem> taskItemList)
        {
            jsonTestSequence.SaveJsonFile(jsonFile, taskItemList);
        }
    }
}
