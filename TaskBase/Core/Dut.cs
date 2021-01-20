using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;

namespace AILinkFactoryAuto.Core
{
    public class Dut
    {
        private static int count;
        private static Semaphore semaphore = new Semaphore(1, 1);

        public static int Inc()
        {
            semaphore.WaitOne();
            count++;
            semaphore.Release();
            return count;
        }

        public static int Dec()
        {
            semaphore.WaitOne();
            count--;
            semaphore.Release();
            return count;
        }

        public static int GetCount()
        {
            semaphore.WaitOne();
            semaphore.Release();
            return count;
        }

        private int index;

        private string name;

        private string fileName;

        private string projectName;

        private string projectPath;

        public int Index
        {
            get { return index; }
            set { index = value; }
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string FileName
        {
            get { return fileName; }
            set { fileName = value; }
        }

        public string ProjectName
        {
            get { return projectName; }
            set { projectName = value; }
        }

        public string ProjectPath
        {
            get { return projectPath; }
            set { projectPath = value; }
        }

        public static Dut GenDut(string filename)
        {
            Dut dut = new Dut();
            dut.fileName = filename;
            dut.projectPath = Path.GetDirectoryName(filename);

            Match match = Regex.Match(filename, @"\\DUT([0-9]+)_");
            string temp = match.Groups[1].ToString();
            dut.index = int.Parse(match.Groups[1].ToString());
            dut.name = "DUT" + temp;

            match = Regex.Match(filename, @"\\projects\\([\s\S]+)\\");
            dut.projectName = match.Groups[1].ToString();
            return dut;
        }
    }
}
