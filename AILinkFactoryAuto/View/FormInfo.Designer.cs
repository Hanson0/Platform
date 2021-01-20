namespace AILinkFactoryAuto.View
{
    partial class FormInfo
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.rtcInfo = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // rtcInfo
            // 
            this.rtcInfo.Dock = System.Windows.Forms.DockStyle.Fill;
            this.rtcInfo.Location = new System.Drawing.Point(0, 0);
            this.rtcInfo.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rtcInfo.Name = "rtcInfo";
            this.rtcInfo.Size = new System.Drawing.Size(379, 328);
            this.rtcInfo.TabIndex = 0;
            this.rtcInfo.Text = "";
            // 
            // FormInfo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(379, 328);
            this.Controls.Add(this.rtcInfo);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "FormInfo";
            this.Text = "Information";
            this.Load += new System.EventHandler(this.FormInfo_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox rtcInfo;
    }
}