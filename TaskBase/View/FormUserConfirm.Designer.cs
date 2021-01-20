namespace AILinkFactoryAuto.View
{
    partial class FormUserConfirm
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
            this.txtTips = new System.Windows.Forms.TextBox();
            this.lblInfoPass = new System.Windows.Forms.Label();
            this.lblInfoFail = new System.Windows.Forms.Label();
            this.lblCountDown = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // txtTips
            // 
            this.txtTips.Font = new System.Drawing.Font("微软雅黑", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtTips.Location = new System.Drawing.Point(12, 12);
            this.txtTips.Multiline = true;
            this.txtTips.Name = "txtTips";
            this.txtTips.ReadOnly = true;
            this.txtTips.Size = new System.Drawing.Size(560, 252);
            this.txtTips.TabIndex = 0;
            this.txtTips.Text = "用户按键确认";
            // 
            // lblInfoPass
            // 
            this.lblInfoPass.AutoSize = true;
            this.lblInfoPass.Font = new System.Drawing.Font("微软雅黑", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblInfoPass.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.lblInfoPass.Location = new System.Drawing.Point(7, 329);
            this.lblInfoPass.Name = "lblInfoPass";
            this.lblInfoPass.Size = new System.Drawing.Size(457, 62);
            this.lblInfoPass.TabIndex = 1;
            this.lblInfoPass.Text = "PASS：请按Enter键";
            // 
            // lblInfoFail
            // 
            this.lblInfoFail.AutoSize = true;
            this.lblInfoFail.Font = new System.Drawing.Font("微软雅黑", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblInfoFail.ForeColor = System.Drawing.Color.Red;
            this.lblInfoFail.Location = new System.Drawing.Point(7, 391);
            this.lblInfoFail.Name = "lblInfoFail";
            this.lblInfoFail.Size = new System.Drawing.Size(357, 62);
            this.lblInfoFail.TabIndex = 2;
            this.lblInfoFail.Text = "FAIL：请按Q键";
            // 
            // lblCountDown
            // 
            this.lblCountDown.AutoSize = true;
            this.lblCountDown.Font = new System.Drawing.Font("微软雅黑", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblCountDown.ForeColor = System.Drawing.Color.Black;
            this.lblCountDown.Location = new System.Drawing.Point(7, 267);
            this.lblCountDown.Name = "lblCountDown";
            this.lblCountDown.Size = new System.Drawing.Size(267, 62);
            this.lblCountDown.TabIndex = 3;
            this.lblCountDown.Text = "倒计时开始";
            // 
            // FormUserConfirm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 462);
            this.Controls.Add(this.lblCountDown);
            this.Controls.Add(this.lblInfoFail);
            this.Controls.Add(this.lblInfoPass);
            this.Controls.Add(this.txtTips);
            this.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(6);
            this.Name = "FormUserConfirm";
            this.Text = "FormUserConfirm";
            this.Shown += new System.EventHandler(this.FormUserConfirm_Shown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtTips;
        private System.Windows.Forms.Label lblInfoPass;
        private System.Windows.Forms.Label lblInfoFail;
        private System.Windows.Forms.Label lblCountDown;
    }
}