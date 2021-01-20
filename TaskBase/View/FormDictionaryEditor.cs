using System;
using System.Collections;
using System.Windows.Forms;
using AILinkFactoryAuto.Task.Property;

namespace AILinkFactoryAuto.View
{
    public partial class FormDictionaryEditor : Form
    {
        private IDictionary dictionary;

        public IDictionary Dictionary
        {
            get { return dictionary; }
            set { dictionary = value; }
        }

        public FormDictionaryEditor()
        {
            InitializeComponent();
        }

        public FormDictionaryEditor(IDictionary dictionary)
        {
            InitializeComponent();
            this.dictionary = dictionary;
            this.Shown += FormDictionaryEditor_Shown;
            this.listBox.Click += ListBox_Click;
            this.btnAdd.Click += BtnAdd_Click;
            this.btnDel.Click += BtnDel_Click;
        }

        private void BtnDel_Click(object sender, EventArgs e)
        {
            string key = listBox.SelectedItem.ToString();
            if (string.IsNullOrEmpty(key))
            {
                return;
            }
            dictionary.Remove(key);
            FormDictionaryEditor_Shown(null, null);
        }

        private void BtnAdd_Click(object sender, EventArgs e)
        {
            FormAddKey formAddKey = new FormAddKey();
            DialogResult dialogResult = formAddKey.ShowDialog();
            if (dialogResult == DialogResult.OK)
            {
                dictionary.Add(formAddKey.Key, new KeyValue());
                FormDictionaryEditor_Shown(null, null);
            }
        }

        private void ListBox_Click(object sender, EventArgs e)
        {
            if (listBox.SelectedItem == null)
            {
                return;
            }
            string key = listBox.SelectedItem.ToString();
            propertyGrid.SelectedObject = dictionary[key];
        }

        private void FormDictionaryEditor_Shown(object sender, EventArgs e)
        {
            listBox.Items.Clear();
            foreach (DictionaryEntry entry in dictionary)
            {
                listBox.Items.Add(entry.Key);
            }
        }
    }
}
