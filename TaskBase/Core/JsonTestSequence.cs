using System;
using System.Collections.Generic;
using System.IO;
using AILinkFactoryAuto.Task;
using Newtonsoft.Json;

namespace AILinkFactoryAuto.Core
{
    public class JsonTestSequence
    {
        private static string _path = "./projects";

        public string[] GetAllJsonFiles(string projectPath)
        {
            string[] jsonFileList = Directory.GetFiles(projectPath);
            for (int i = 0; i < jsonFileList.Length; i++)
            {
                jsonFileList[i] = jsonFileList[i].Replace(projectPath + "\\", "");
            }

            return jsonFileList;
        }

        public List<TaskItem> GetTaskItemListFromFileName(string projectPath, string jtsFileName)
        {
            string fullFileName = Path.Combine(projectPath, jtsFileName);
            try
            {
                return GetTaskItemListFromFullFileName(fullFileName);
            }
            catch (Exception e)
            {
                Box.ShowInfoOk(e.ToString());
                return null;
            }
        }

        public void SaveJsonFile(string filename, List<TaskItem> taskItemList)
        {
            if (taskItemList == null || taskItemList.Count == 0)
            {
                return;
            }

            if (string.IsNullOrEmpty(Path.GetDirectoryName(filename)))
            {
                filename = Path.Combine(_path, filename);
            }

            JsonSerializerSettings settings = new JsonSerializerSettings();
            settings.TypeNameHandling = TypeNameHandling.All;
            string jts = JsonConvert.SerializeObject(taskItemList, Formatting.Indented, settings);
            File.WriteAllText(filename, jts);
        }

        public string GetJsonFile( List<TaskItem> taskItemList)
        {
            //SetDefaultJsonFile(filename);
            //string fullFileName = GetDefaultJtsFullFileName(filename);

            if (taskItemList == null || taskItemList.Count == 0)
            {
                return "";
            }

            JsonSerializerSettings settings = new JsonSerializerSettings();
            settings.TypeNameHandling = TypeNameHandling.All;
            string jts = JsonConvert.SerializeObject(taskItemList, Formatting.Indented, settings);
            return jts;
        }

        public List<TaskItem> GetTaskItemListFromFullFileName(string jsonFile)
        {
            string content = File.ReadAllText(jsonFile);
            JsonSerializerSettings settings = new JsonSerializerSettings();
            settings.TypeNameHandling = TypeNameHandling.Auto;
            return JsonConvert.DeserializeObject<List<TaskItem>>(content, settings);
        }
    }
}
