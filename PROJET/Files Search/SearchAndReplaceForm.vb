Imports System
Imports System.Drawing
Imports System.Collections
Imports System.ComponentModel
Imports System.Windows.Forms
Imports System.Text.RegularExpressions

    Public Interface ISearchAndReplaceFormParent

        Sub SetCursorPos(ByVal CursorPos As Integer)

        Function GetText() As String

        Sub SetText(ByVal Text As String)

        Function GetSelectionStart() As Integer

    Sub sSelect(ByVal Start As Integer, ByVal Length As Integer)

    Function GetTextNotFoundCaption() As String
End Interface

    Public Class SearchAndReplaceForm
        Inherits System.Windows.Forms.Form
        Private label1 As System.Windows.Forms.Label
        Private panel1 As System.Windows.Forms.Panel
        Private UpRadioButton As System.Windows.Forms.RadioButton
        Private DownRadioButton As System.Windows.Forms.RadioButton
        Private CloseButton As System.Windows.Forms.Button
        Private FindTextBox As System.Windows.Forms.TextBox
        Private FindNextButton As System.Windows.Forms.Button
        Private MatchCaseCheckBox As System.Windows.Forms.CheckBox
        Private WholeWorldCheckBox As System.Windows.Forms.CheckBox
        Private ReplaceButton As System.Windows.Forms.Button
        Private ReplaceLabel As System.Windows.Forms.Label
        Private ReplaceTextBox As System.Windows.Forms.TextBox
        Private ReplaceAllButton As System.Windows.Forms.Button
        Private TEParent As ISearchAndReplaceFormParent
        Private components As System.ComponentModel.Container = Nothing
        Private Shared FindText As String = ""
        Private Shared ReplaceText As String = ""
        Private Shared MatchCase As Boolean = False
        Private Shared WholeWord As Boolean = False
        Private Shared Up As Boolean = False

        Public Sub New(ByVal Parent As Object, ByVal AllowReplace As Boolean)
            InitializeComponent()
            FindTextBox.Text = FindText
            ReplaceTextBox.Text = ReplaceText
            MatchCaseCheckBox.Checked = MatchCase
            WholeWorldCheckBox.Checked = WholeWord
            UpRadioButton.Checked = Up
            DownRadioButton.Checked = Not Up
            TEParent = CType(Parent, ISearchAndReplaceFormParent)
            If AllowReplace Then
                ReplaceButton.Visible = True
                ReplaceButton.Enabled = False
                ReplaceAllButton.Visible = True
                ReplaceAllButton.Enabled = False
                ReplaceTextBox.Visible = True
                ReplaceTextBox.Enabled = True
                ReplaceLabel.Visible = True
                ReplaceLabel.Enabled = True
                Text = "Find and Replace"
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
            Me.label1 = New System.Windows.Forms.Label
            Me.FindTextBox = New System.Windows.Forms.TextBox
            Me.panel1 = New System.Windows.Forms.Panel
            Me.DownRadioButton = New System.Windows.Forms.RadioButton
            Me.UpRadioButton = New System.Windows.Forms.RadioButton
            Me.MatchCaseCheckBox = New System.Windows.Forms.CheckBox
            Me.WholeWorldCheckBox = New System.Windows.Forms.CheckBox
            Me.CloseButton = New System.Windows.Forms.Button
            Me.FindNextButton = New System.Windows.Forms.Button
            Me.ReplaceLabel = New System.Windows.Forms.Label
            Me.ReplaceTextBox = New System.Windows.Forms.TextBox
            Me.ReplaceButton = New System.Windows.Forms.Button
            Me.ReplaceAllButton = New System.Windows.Forms.Button
            Me.panel1.SuspendLayout()
            Me.SuspendLayout()
            Me.label1.Location = New System.Drawing.Point(8, 8)
            Me.label1.Name = "label1"
            Me.label1.Size = New System.Drawing.Size(40, 23)
            Me.label1.TabIndex = 0
            Me.label1.Text = "&Find:"
            Me.FindTextBox.Location = New System.Drawing.Point(80, 8)
            Me.FindTextBox.Name = "FindTextBox"
            Me.FindTextBox.Size = New System.Drawing.Size(248, 22)
            Me.FindTextBox.TabIndex = 1
            Me.FindTextBox.Text = ""
            AddHandler Me.FindTextBox.TextChanged, AddressOf Me.FindTextBox_TextChanged
            Me.panel1.Controls.AddRange(New System.Windows.Forms.Control() {Me.DownRadioButton, Me.UpRadioButton})
            Me.panel1.Location = New System.Drawing.Point(128, 80)
            Me.panel1.Name = "panel1"
            Me.panel1.Size = New System.Drawing.Size(88, 72)
            Me.panel1.TabIndex = 6
            Me.DownRadioButton.Checked = True
            Me.DownRadioButton.Location = New System.Drawing.Point(16, 40)
            Me.DownRadioButton.Name = "DownRadioButton"
            Me.DownRadioButton.Size = New System.Drawing.Size(64, 24)
            Me.DownRadioButton.TabIndex = 1
            Me.DownRadioButton.TabStop = True
            Me.DownRadioButton.Text = "&Down"
            Me.UpRadioButton.Location = New System.Drawing.Point(16, 8)
            Me.UpRadioButton.Name = "UpRadioButton"
            Me.UpRadioButton.Size = New System.Drawing.Size(64, 24)
            Me.UpRadioButton.TabIndex = 0
            Me.UpRadioButton.Text = "&Up"
            Me.MatchCaseCheckBox.Location = New System.Drawing.Point(8, 88)
            Me.MatchCaseCheckBox.Name = "MatchCaseCheckBox"
            Me.MatchCaseCheckBox.Size = New System.Drawing.Size(112, 24)
            Me.MatchCaseCheckBox.TabIndex = 4
            Me.MatchCaseCheckBox.Text = "&Match Case"
            Me.WholeWorldCheckBox.Location = New System.Drawing.Point(8, 120)
            Me.WholeWorldCheckBox.Name = "WholeWorldCheckBox"
            Me.WholeWorldCheckBox.Size = New System.Drawing.Size(112, 24)
            Me.WholeWorldCheckBox.TabIndex = 5
            Me.WholeWorldCheckBox.Text = "&Whole Word"
            Me.CloseButton.DialogResult = System.Windows.Forms.DialogResult.Cancel
            Me.CloseButton.Location = New System.Drawing.Point(232, 184)
            Me.CloseButton.Name = "CloseButton"
            Me.CloseButton.Size = New System.Drawing.Size(96, 23)
            Me.CloseButton.TabIndex = 10
            Me.CloseButton.Text = "&Close"
            AddHandler Me.CloseButton.Click, AddressOf Me.CloseButton_Click
            Me.FindNextButton.Enabled = False
            Me.FindNextButton.Location = New System.Drawing.Point(232, 72)
            Me.FindNextButton.Name = "FindNextButton"
            Me.FindNextButton.Size = New System.Drawing.Size(96, 23)
            Me.FindNextButton.TabIndex = 7
            Me.FindNextButton.Text = "Find &Next"
            AddHandler Me.FindNextButton.Click, AddressOf Me.FindNextButton_Click
            Me.ReplaceLabel.Enabled = False
            Me.ReplaceLabel.Location = New System.Drawing.Point(8, 40)
            Me.ReplaceLabel.Name = "ReplaceLabel"
            Me.ReplaceLabel.Size = New System.Drawing.Size(64, 23)
            Me.ReplaceLabel.TabIndex = 2
            Me.ReplaceLabel.Text = "Re&place:"
            Me.ReplaceLabel.Visible = False
            Me.ReplaceTextBox.Enabled = False
            Me.ReplaceTextBox.Location = New System.Drawing.Point(80, 40)
            Me.ReplaceTextBox.Name = "ReplaceTextBox"
            Me.ReplaceTextBox.Size = New System.Drawing.Size(248, 22)
            Me.ReplaceTextBox.TabIndex = 3
            Me.ReplaceTextBox.Text = ""
            Me.ReplaceTextBox.Visible = False
            Me.ReplaceButton.Enabled = False
            Me.ReplaceButton.Location = New System.Drawing.Point(232, 104)
            Me.ReplaceButton.Name = "ReplaceButton"
            Me.ReplaceButton.Size = New System.Drawing.Size(96, 23)
            Me.ReplaceButton.TabIndex = 8
            Me.ReplaceButton.Text = "&Replace"
            Me.ReplaceButton.Visible = False
            AddHandler Me.ReplaceButton.Click, AddressOf Me.ReplaceButton_Click
            Me.ReplaceAllButton.Enabled = False
            Me.ReplaceAllButton.Location = New System.Drawing.Point(232, 136)
            Me.ReplaceAllButton.Name = "ReplaceAllButton"
            Me.ReplaceAllButton.Size = New System.Drawing.Size(96, 23)
            Me.ReplaceAllButton.TabIndex = 9
            Me.ReplaceAllButton.Text = "Replace &All"
            Me.ReplaceAllButton.Visible = False
            AddHandler Me.ReplaceAllButton.Click, AddressOf Me.ReplaceAllButton_Click
            Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
            Me.CancelButton = Me.CloseButton
            Me.ClientSize = New System.Drawing.Size(336, 215)
            Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.ReplaceAllButton, Me.ReplaceButton, Me.ReplaceTextBox, Me.ReplaceLabel, Me.FindNextButton, Me.CloseButton, Me.WholeWorldCheckBox, Me.MatchCaseCheckBox, Me.panel1, Me.FindTextBox, Me.label1})
            Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
            Me.MaximizeBox = False
            Me.MinimizeBox = False
            Me.Name = "SearchAndReplaceForm"
            Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
            Me.Text = "Find"
            Me.TopMost = True
            AddHandler Me.Closing, AddressOf Me.SearchAndReplaceForm_Closing
            AddHandler Me.Load, AddressOf Me.SearchAndReplaceForm_Load
            Me.panel1.ResumeLayout(False)
            Me.ResumeLayout(False)
        End Sub

        Private Sub CloseButton_Click(ByVal sender As Object, ByVal e As System.EventArgs)
            Close()
        End Sub

        Private Sub SearchAndReplaceForm_Load(ByVal sender As Object, ByVal e As System.EventArgs)
            ActiveControl = FindTextBox
        End Sub

        Private Sub FindTextBox_TextChanged(ByVal sender As Object, ByVal e As System.EventArgs)
            FindNextButton.Enabled = FindTextBox.Text.Length > 0
        End Sub

        Private Sub EnableReplace(ByVal Enabled As Boolean)
            If ReplaceButton.Visible Then
                ReplaceButton.Enabled = Enabled
                ReplaceAllButton.Enabled = Enabled
            End If
        End Sub

        Private Sub TextNotFound()
            MessageBox.Show("Text not found.", TEParent.GetTextNotFoundCaption, MessageBoxButtons.OK, MessageBoxIcon.Information)
        End Sub

        Private Function GetREPattern() As String
            Dim Result As String = EscapeSearchPattern(FindTextBox.Text)
            If WholeWorldCheckBox.Checked Then
                Dim WordBoundry As String = "[^a-zA-Z]"
                Result = WordBoundry + Result + WordBoundry
            End If
            Return Result
        End Function

        Private Function GetRegexOptions() As RegexOptions
            Dim Result As RegexOptions = RegexOptions.None
            If Not MatchCaseCheckBox.Checked Then
                Result = Result Or (RegexOptions.IgnoreCase)
            End If
            Return Result
        End Function

        Private Function EscapeSearchPattern(ByVal SearchPattern As String) As String
            Dim Result As String = ""
            For Each C As Char In SearchPattern
                If (C >= "a"c AndAlso C <= "z"c) OrElse (C >= "A"c AndAlso C <= "Z"c) OrElse (C >= "0"c AndAlso C <= "9"c) OrElse (C = "_"c) Then
                    Result += C
                Else
                    Result += "\" + C
                End If
            Next
            Return Result
        End Function

        Private Sub FindNextButton_Click(ByVal sender As Object, ByVal e As System.EventArgs)
            Dim Text As String = TEParent.GetText
            Dim REPattern As String = GetREPattern
            Dim Options As RegexOptions = GetRegexOptions
            Dim R As Regex = New Regex(REPattern, Options)
            Dim SelectionStart As Integer = TEParent.GetSelectionStart
            If DownRadioButton.Checked Then
                If SelectionStart < Text.Length Then
                    Dim M As MatchCollection = R.Matches(Text, SelectionStart + 1)
                    If M.Count > 0 Then
                    TEParent.sSelect(M(0).Index, M(0).Length)
                        EnableReplace(True)
                    Else
                        EnableReplace(False)
                        TextNotFound()
                    End If
                Else
                    EnableReplace(False)
                    TextNotFound()
                End If
            Else
                Dim M As MatchCollection = R.Matches(Text, 0)
                Dim Index As Integer = -1
                Dim Length As Integer = -1
                For Each CurrentMatch As Match In M
                    If CurrentMatch.Index > Index AndAlso CurrentMatch.Index < SelectionStart Then
                        Index = CurrentMatch.Index
                        Length = CurrentMatch.Length
                    End If
                Next
                If Not (Index = -1) Then
                TEParent.sSelect(Index, Length)
                    EnableReplace(True)
                Else
                    EnableReplace(False)
                    TextNotFound()
                End If
            End If
        End Sub

        Private Sub ReplaceButton_Click(ByVal sender As Object, ByVal e As System.EventArgs)
            Dim SelectionStart As Integer = TEParent.GetSelectionStart
            Dim Text As String = TEParent.GetText
            If SelectionStart >= 0 AndAlso SelectionStart < Text.Length Then
                Text = Text.Remove(SelectionStart, FindTextBox.Text.Length)
                Text = Text.Insert(SelectionStart, ReplaceTextBox.Text)
                TEParent.SetText(Text)
                If DownRadioButton.Checked Then
                    SelectionStart += ReplaceTextBox.TextLength
                End If
                TEParent.SetCursorPos(SelectionStart)
                EnableReplace(False)
            End If
        End Sub

        Private Sub ReplaceAllButton_Click(ByVal sender As Object, ByVal e As System.EventArgs)
            Dim Text As String = TEParent.GetText
            Dim REPattern As String = GetREPattern
            Dim Options As RegexOptions = GetRegexOptions
            Dim R As Regex = New Regex(REPattern, Options)
            Dim SelectionStart As Integer = TEParent.GetSelectionStart
            Dim M As MatchCollection = R.Matches(Text, 0)
            Dim i As Integer = M.Count - 1
            While i >= 0
                If (DownRadioButton.Checked AndAlso M(i).Index > SelectionStart) OrElse (UpRadioButton.Checked AndAlso M(i).Index < SelectionStart) Then
                    Text = Text.Remove(M(i).Index, FindTextBox.Text.Length)
                    Text = Text.Insert(M(i).Index, ReplaceTextBox.Text)
                End If
                System.Math.Max(System.Threading.Interlocked.Decrement(i), i + 1)
            End While
            TEParent.SetText(Text)
            If DownRadioButton.Checked Then
                TEParent.SetCursorPos(TEParent.GetText.Length)
            Else
                TEParent.SetCursorPos(0)
            End If
            ReplaceButton.Enabled = ReplaceAllButton.Enabled = False
        End Sub

        Private Sub SearchAndReplaceForm_Closing(ByVal sender As Object, ByVal e As System.ComponentModel.CancelEventArgs)
            FindText = FindTextBox.Text
            ReplaceText = ReplaceTextBox.Text
            MatchCase = MatchCaseCheckBox.Checked
            Up = UpRadioButton.Checked
            WholeWord = WholeWorldCheckBox.Checked
        End Sub
    End Class
