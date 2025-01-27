Imports System
Imports System.Drawing
Imports System.Collections
Imports System.ComponentModel
Imports System.Windows.Forms

    Public Class AboutForm
        Inherits System.Windows.Forms.Form
        Private label1 As System.Windows.Forms.Label
        Private label2 As System.Windows.Forms.Label
        Private label3 As System.Windows.Forms.Label
        Private CloseButton As System.Windows.Forms.Button
        Private VisitOurWebSiteButton As System.Windows.Forms.Button
        Private components As System.ComponentModel.Container = Nothing

        Public Sub New()
            InitializeComponent()
        End Sub

        Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
            If disposing Then
                If Not (components Is Nothing) Then
                    components.Dispose()
                End If
            End If
            MyBase.Dispose(disposing)
        End Sub

        Private Sub InitializeComponent()
            Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(AboutForm))
            Me.label1 = New System.Windows.Forms.Label
            Me.label2 = New System.Windows.Forms.Label
            Me.label3 = New System.Windows.Forms.Label
            Me.CloseButton = New System.Windows.Forms.Button
            Me.VisitOurWebSiteButton = New System.Windows.Forms.Button
            Me.SuspendLayout()
            Me.label1.Location = New System.Drawing.Point(8, 16)
            Me.label1.Name = "label1"
            Me.label1.Size = New System.Drawing.Size(264, 48)
            Me.label1.TabIndex = 0
            Me.label1.Text = "File Search was written by Eric Bergman-Terrell"
            Me.label2.Location = New System.Drawing.Point(8, 72)
            Me.label2.Name = "label2"
            Me.label2.Size = New System.Drawing.Size(264, 24)
            Me.label2.TabIndex = 1
            Me.label2.Text = "Personal MicroCosms"
            Me.label3.Location = New System.Drawing.Point(8, 104)
            Me.label3.Name = "label3"
            Me.label3.Size = New System.Drawing.Size(264, 24)
            Me.label3.TabIndex = 2
            Me.label3.Text = "www.PersonalMicroCosms.com"
            Me.CloseButton.DialogResult = System.Windows.Forms.DialogResult.Cancel
            Me.CloseButton.Location = New System.Drawing.Point(26, 144)
            Me.CloseButton.Name = "CloseButton"
            Me.CloseButton.TabIndex = 3
            Me.CloseButton.Text = "&Close"
            Me.VisitOurWebSiteButton.Location = New System.Drawing.Point(122, 144)
            Me.VisitOurWebSiteButton.Name = "VisitOurWebSiteButton"
            Me.VisitOurWebSiteButton.Size = New System.Drawing.Size(132, 23)
            Me.VisitOurWebSiteButton.TabIndex = 4
            Me.VisitOurWebSiteButton.Text = "&Visit Our Website"
            AddHandler Me.VisitOurWebSiteButton.Click, AddressOf Me.VisitOurWebSiteButton_Click
            Me.AcceptButton = Me.CloseButton
            Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
            Me.CancelButton = Me.CloseButton
            Me.ClientSize = New System.Drawing.Size(280, 180)
            Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.VisitOurWebSiteButton, Me.CloseButton, Me.label3, Me.label2, Me.label1})
            Me.Icon = CType((resources.GetObject("$this.Icon")), System.Drawing.Icon)
            Me.MaximizeBox = False
            Me.MinimizeBox = False
            Me.Name = "AboutForm"
            Me.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide
            Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
            Me.Text = "About File Search"
            Me.ResumeLayout(False)
        End Sub

        Private Sub CloseButton_Click(ByVal sender As Object, ByVal e As System.EventArgs)
            Close()
        End Sub

        Private Sub VisitOurWebSiteButton_Click(ByVal sender As Object, ByVal e As System.EventArgs)
            Try
                System.Diagnostics.Process.Start("http://www.PersonalMicroCosms.com")
            Catch generatedExceptionVariable0 As Exception
            End Try
        End Sub
    End Class
