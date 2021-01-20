using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AILinkFactoryAuto.Utils
{
    public interface IGenJts
    {
        string ProjectPath { get; set; }

        DialogResult ShowDialog();

        FormStartPosition StartPosition { get; set; }
    }
}
