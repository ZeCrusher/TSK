Imports System
Imports System.Drawing
Imports System.Collections
Imports System.ComponentModel
Imports System.Windows.Forms
Imports System.IO

    Public Class BrowseForFolderForm
        Inherits System.Windows.Forms.Form
        Private m_TreeView As System.Windows.Forms.TreeView
        Private label1 As System.Windows.Forms.Label
        Private OKButton As System.Windows.Forms.Button
        Private FolderTextBox As System.Windows.Forms.TextBox
        Private m_CancelButton As System.Windows.Forms.Button
        Public Shared m_FolderPath As String
        Private components As System.ComponentModel.Container = Nothing

        Public Sub New(ByVal FolderPath As String)
            InitializeComponent()
            If Directory.Exists(FolderPath.Trim) Then
                m_FolderPath = Path.GetFullPath(FolderPath.Trim)
            Else
                m_FolderPath = ""
            End If
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
            Me.m_TreeView = New System.Windows.Forms.TreeView
            Me.label1 = New System.Windows.Forms.Label
            Me.OKButton = New System.Windows.Forms.Button
            Me.FolderTextBox = New System.Windows.Forms.TextBox
            Me.m_CancelButton = New System.Windows.Forms.Button
            Me.SuspendLayout()
            Me.m_TreeView.Anchor = (((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) Or System.Windows.Forms.AnchorStyles.Left) Or System.Windows.Forms.AnchorStyles.Right)
            Me.m_TreeView.ImageIndex = -1
            Me.m_TreeView.Location = New System.Drawing.Point(8, 8)
            Me.m_TreeView.Name = "m_TreeView"
            Me.m_TreeView.SelectedImageIndex = -1
            Me.m_TreeView.Size = New System.Drawing.Size(432, 256)
            Me.m_TreeView.TabIndex = 0
            AddHandler Me.m_TreeView.AfterSelect, AddressOf Me.m_TreeView_AfterSelect
            AddHandler Me.m_TreeView.BeforeExpand, AddressOf Me.m_TreeView_BeforeExpand
            Me.label1.Anchor = (System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left)
            Me.label1.Location = New System.Drawing.Point(8, 272)
            Me.label1.Name = "label1"
            Me.label1.TabIndex = 1
            Me.label1.Text = "Folder:"
            Me.OKButton.Anchor = (System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left)
            Me.OKButton.Location = New System.Drawing.Point(134, 336)
            Me.OKButton.Name = "OKButton"
            Me.OKButton.TabIndex = 3
            Me.OKButton.Text = "&OK"
            AddHandler Me.OKButton.Click, AddressOf Me.OKButton_Click
            Me.FolderTextBox.Anchor = ((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left) Or System.Windows.Forms.AnchorStyles.Right)
            Me.FolderTextBox.Location = New System.Drawing.Point(8, 296)
            Me.FolderTextBox.Name = "FolderTextBox"
            Me.FolderTextBox.Size = New System.Drawing.Size(432, 22)
            Me.FolderTextBox.TabIndex = 5
            Me.FolderTextBox.Text = ""
            Me.m_CancelButton.Anchor = (System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left)
            Me.m_CancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel
            Me.m_CancelButton.Location = New System.Drawing.Point(239, 336)
            Me.m_CancelButton.Name = "m_CancelButton"
            Me.m_CancelButton.TabIndex = 6
            Me.m_CancelButton.Text = "&Cancel"
            Me.AcceptButton = Me.OKButton
            Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
            Me.CancelButton = Me.m_CancelButton
            Me.ClientSize = New System.Drawing.Size(448, 364)
            Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.m_CancelButton, Me.FolderTextBox, Me.OKButton, Me.label1, Me.m_TreeView})
            Me.MinimizeBox = False
            Me.MinimumSize = New System.Drawing.Size(456, 392)
            Me.Name = "BrowseForFolderForm"
            Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
            Me.Text = "Browse For Folder"
            AddHandler Me.Load, AddressOf Me.BrowseForFolderForm_Load
            Me.ResumeLayout(False)
        End Sub

        Private Sub BrowseForFolderForm_Load(ByVal sender As Object, ByVal e As System.EventArgs)
            Cursor.Current = Cursors.WaitCursor
            Dim Drives As String() = Directory.GetLogicalDrives
            For Each Dir As String In Drives
                If Directory.Exists(Dir) Then
                    If DirectoryHasSubDirectories(Dir) Then
                        Dim Children As TreeNode() = {New TreeNode("")}
                        m_TreeView.Nodes.Add(New TreeNode(Dir, Children))
                    Else
                        m_TreeView.Nodes.Add(New TreeNode(Dir))
                    End If
                End If
            Next
            If Directory.Exists(m_FolderPath) Then
                Dim Root As String = Path.GetPathRoot(m_FolderPath)
                For Each T As TreeNode In m_TreeView.Nodes
                    If String.Compare(T.Text.Trim, Root, True) = 0 Then
                        m_TreeView.SelectedNode = T
                        m_TreeView.SelectedNode.Expand()
                        ' break
                    End If
                Next
                Dim Index As Integer
                Dim Tmp As String = m_FolderPath
                Do
                    Index = Tmp.IndexOf("\")
                    If Not (Index = -1) Then
                        Dim Folder As String = Tmp.Substring(Index + 1)
                        Dim Index2 As Integer = Folder.IndexOf("\")
                        If Not (Index2 = -1) Then
                            Folder = Folder.Substring(0, Index2)
                        End If
                        For Each T As TreeNode In m_TreeView.SelectedNode.Nodes
                            If String.Compare(T.Text.Trim, Folder, True) = 0 Then
                                m_TreeView.SelectedNode = T
                                If Tmp.LastIndexOf("\") > Index Then
                                    m_TreeView.SelectedNode.Expand()
                                End If
                                ' break
                            End If
                        Next
                        Tmp = Tmp.Substring(Index + 1)
                    End If
                Loop While Not (Index = -1)
            End If
            m_FolderPath = ""
            Cursor.Current = Cursors.Arrow
        End Sub

        Private Shared Function DirectoryHasSubDirectories(ByVal Dir As String) As Boolean
            Dim Result As Boolean
            Try
                Result = Directory.GetDirectories(Dir).Length > 0
            Catch generatedExceptionVariable0 As Exception
                Result = False
            End Try
            Return Result
        End Function

        Private Shared Function GetPath(ByVal Node As TreeNode) As String
            Dim Result As String = ""
            If Not (Node Is Nothing) Then
                Result = Node.Text
                If Not (Node.Parent Is Nothing) Then
                    Result = GetPath(Node.Parent) + "\" + Result
                End If
            End If
            Return Result
        End Function

        Private Shared Function GetDirectoryName(ByVal Path As String) As String
            Dim Result As String = ""
            Dim nIndex As Integer = Path.LastIndexOf("\")
            If Not (nIndex = -1) Then
                Result = Path.Substring(nIndex + 1)
            End If
            Return Result
        End Function

        Private Sub m_TreeView_BeforeExpand(ByVal sender As Object, ByVal e As System.Windows.Forms.TreeViewCancelEventArgs)
            Cursor.Current = Cursors.WaitCursor
            If e.Node.Nodes.Count = 1 AndAlso e.Node.Nodes(0).Text.Length = 0 Then
                e.Node.Nodes.RemoveAt(0)
                For Each Dir As String In Directory.GetDirectories(GetPath(e.Node))
                    If Not DirectoryHasSubDirectories(Dir) Then
                        e.Node.Nodes.Add(GetDirectoryName(Dir))
                    Else
                        Dim Children As TreeNode() = {New TreeNode("")}
                        e.Node.Nodes.Add(New TreeNode(GetDirectoryName(Dir), Children))
                    End If
                Next
            End If
            Cursor.Current = Cursors.Arrow
        End Sub

        Private Sub m_TreeView_AfterSelect(ByVal sender As Object, ByVal e As System.Windows.Forms.TreeViewEventArgs)
            If m_FolderPath.Length = 0 Then
                FolderTextBox.Text = GetPath(e.Node).Replace("\\", "\")
            Else
                FolderTextBox.Text = m_FolderPath
            End If
        End Sub

        Private Sub OKButton_Click(ByVal sender As Object, ByVal e As System.EventArgs)
            If Directory.Exists(FolderTextBox.Text) Then
                m_FolderPath = FolderTextBox.Text
                DialogResult = DialogResult.OK
                Close()
            Else
                MessageBox.Show("Folder does not exist", "Browse for Folder", MessageBoxButtons.OK, MessageBoxIcon.Stop)
            End If
        End Sub
    End Class
