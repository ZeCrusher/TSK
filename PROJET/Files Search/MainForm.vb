Imports System
Imports System.Drawing
Imports System.Collections
Imports System.ComponentModel
Imports System.Windows.Forms
Imports System.Data
Imports System.IO
Imports System.Collections.Specialized
Imports System.Threading

Public Class MainForm
    Inherits System.Windows.Forms.Form
    Private label1 As System.Windows.Forms.Label
    Private FileNameTextBox As System.Windows.Forms.TextBox
    Private ContainingTextBox As System.Windows.Forms.TextBox
    Private groupBox1 As System.Windows.Forms.GroupBox
    Private panel1 As System.Windows.Forms.Panel
    Private RegularExpressionRadioButton As System.Windows.Forms.RadioButton
    Private TextRadioButton As System.Windows.Forms.RadioButton
    Private WithEvents ResultsListBox As System.Windows.Forms.ListBox
    Private WithEvents SearchNowButton As System.Windows.Forms.Button
    Private WithEvents StopSearchButton As System.Windows.Forms.Button
    Private CaseSensitiveCheckBox As System.Windows.Forms.CheckBox
    Private label4 As System.Windows.Forms.Label
    Protected FileContentsRichTextBox As System.Windows.Forms.RichTextBox
    Private groupBox2 As System.Windows.Forms.GroupBox
    Private DisksListBox As System.Windows.Forms.CheckedListBox
    Private WithEvents BrowseButton As System.Windows.Forms.Button
    Private WithEvents RemoveButton As System.Windows.Forms.Button
    Private SearchThread As Thread = Nothing
    Private SearchPattern As String = ""
    Private InProgress As Boolean = False
    Private TheStatusBar As System.Windows.Forms.StatusBar
    Private WithEvents RegularExpressionsHelpButton As System.Windows.Forms.Button
    Private WithEvents TheMainMenu As System.Windows.Forms.MainMenu
    Private WithEvents FileMenuItem As System.Windows.Forms.MenuItem
    Private WithEvents FileExitMenuItem As System.Windows.Forms.MenuItem
    Private WithEvents HelpMenuItem As System.Windows.Forms.MenuItem
    Private WithEvents HelpAboutMenuItem As System.Windows.Forms.MenuItem
    Private WithEvents VisitOurWebSiteMenuItem As System.Windows.Forms.MenuItem
    Private WithEvents HelpOnRegularExpressionsMenuItem As System.Windows.Forms.MenuItem
    Private WithEvents menuItem3 As System.Windows.Forms.MenuItem
    Private ResultsLabel As System.Windows.Forms.Label
    Private ContainingText As String = ""
    Private CaseSensitive As Boolean = False
    Private RegularExpression As Boolean = False
    Private Dirs As ArrayList = New ArrayList
    Private SearchMenuItem As System.Windows.Forms.MenuItem
    Private WithEvents SearchFileContentsMenuItem As System.Windows.Forms.MenuItem
    Private m_SearchAndReplaceForm As SearchAndReplaceForm = Nothing
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
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(MainForm))
        Me.label1 = New System.Windows.Forms.Label
        Me.FileNameTextBox = New System.Windows.Forms.TextBox
        Me.ContainingTextBox = New System.Windows.Forms.TextBox
        Me.groupBox1 = New System.Windows.Forms.GroupBox
        Me.RegularExpressionsHelpButton = New System.Windows.Forms.Button
        Me.CaseSensitiveCheckBox = New System.Windows.Forms.CheckBox
        Me.panel1 = New System.Windows.Forms.Panel
        Me.RegularExpressionRadioButton = New System.Windows.Forms.RadioButton
        Me.TextRadioButton = New System.Windows.Forms.RadioButton
        Me.SearchNowButton = New System.Windows.Forms.Button
        Me.StopSearchButton = New System.Windows.Forms.Button
        Me.ResultsLabel = New System.Windows.Forms.Label
        Me.ResultsListBox = New System.Windows.Forms.ListBox
        Me.label4 = New System.Windows.Forms.Label
        Me.FileContentsRichTextBox = New System.Windows.Forms.RichTextBox
        Me.groupBox2 = New System.Windows.Forms.GroupBox
        Me.RemoveButton = New System.Windows.Forms.Button
        Me.BrowseButton = New System.Windows.Forms.Button
        Me.DisksListBox = New System.Windows.Forms.CheckedListBox
        Me.TheStatusBar = New System.Windows.Forms.StatusBar
        Me.TheMainMenu = New System.Windows.Forms.MainMenu
        Me.FileMenuItem = New System.Windows.Forms.MenuItem
        Me.FileExitMenuItem = New System.Windows.Forms.MenuItem
        Me.SearchMenuItem = New System.Windows.Forms.MenuItem
        Me.SearchFileContentsMenuItem = New System.Windows.Forms.MenuItem
        Me.HelpMenuItem = New System.Windows.Forms.MenuItem
        Me.HelpAboutMenuItem = New System.Windows.Forms.MenuItem
        Me.VisitOurWebSiteMenuItem = New System.Windows.Forms.MenuItem
        Me.menuItem3 = New System.Windows.Forms.MenuItem
        Me.HelpOnRegularExpressionsMenuItem = New System.Windows.Forms.MenuItem
        Me.groupBox1.SuspendLayout()
        Me.panel1.SuspendLayout()
        Me.groupBox2.SuspendLayout()
        Me.SuspendLayout()
        '
        'label1
        '
        Me.label1.Location = New System.Drawing.Point(7, 7)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(413, 20)
        Me.label1.TabIndex = 0
        Me.label1.Text = "Search for the following file t&ypes (comma separated, for example:  *.txt, *.vb)" & _
        ":"
        '
        'FileNameTextBox
        '
        Me.FileNameTextBox.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.FileNameTextBox.Location = New System.Drawing.Point(7, 28)
        Me.FileNameTextBox.Name = "FileNameTextBox"
        Me.FileNameTextBox.Size = New System.Drawing.Size(586, 20)
        Me.FileNameTextBox.TabIndex = 1
        Me.FileNameTextBox.Text = ""
        '
        'ContainingTextBox
        '
        Me.ContainingTextBox.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.ContainingTextBox.Location = New System.Drawing.Point(7, 21)
        Me.ContainingTextBox.Name = "ContainingTextBox"
        Me.ContainingTextBox.Size = New System.Drawing.Size(573, 20)
        Me.ContainingTextBox.TabIndex = 0
        Me.ContainingTextBox.Text = ""
        '
        'groupBox1
        '
        Me.groupBox1.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.groupBox1.Controls.Add(Me.RegularExpressionsHelpButton)
        Me.groupBox1.Controls.Add(Me.CaseSensitiveCheckBox)
        Me.groupBox1.Controls.Add(Me.panel1)
        Me.groupBox1.Controls.Add(Me.ContainingTextBox)
        Me.groupBox1.Location = New System.Drawing.Point(7, 62)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Size = New System.Drawing.Size(586, 84)
        Me.groupBox1.TabIndex = 2
        Me.groupBox1.TabStop = False
        Me.groupBox1.Text = "&Containing"
        '
        'RegularExpressionsHelpButton
        '
        Me.RegularExpressionsHelpButton.Location = New System.Drawing.Point(400, 49)
        Me.RegularExpressionsHelpButton.Name = "RegularExpressionsHelpButton"
        Me.RegularExpressionsHelpButton.Size = New System.Drawing.Size(180, 23)
        Me.RegularExpressionsHelpButton.TabIndex = 3
        Me.RegularExpressionsHelpButton.Text = "Help on Regular E&xpressions"
        '
        'CaseSensitiveCheckBox
        '
        Me.CaseSensitiveCheckBox.Location = New System.Drawing.Point(272, 49)
        Me.CaseSensitiveCheckBox.Name = "CaseSensitiveCheckBox"
        Me.CaseSensitiveCheckBox.Size = New System.Drawing.Size(107, 20)
        Me.CaseSensitiveCheckBox.TabIndex = 2
        Me.CaseSensitiveCheckBox.Text = "Case Sensiti&ve"
        '
        'panel1
        '
        Me.panel1.Controls.Add(Me.RegularExpressionRadioButton)
        Me.panel1.Controls.Add(Me.TextRadioButton)
        Me.panel1.Location = New System.Drawing.Point(7, 42)
        Me.panel1.Name = "panel1"
        Me.panel1.Size = New System.Drawing.Size(241, 34)
        Me.panel1.TabIndex = 1
        '
        'RegularExpressionRadioButton
        '
        Me.RegularExpressionRadioButton.Location = New System.Drawing.Point(60, 7)
        Me.RegularExpressionRadioButton.Name = "RegularExpressionRadioButton"
        Me.RegularExpressionRadioButton.Size = New System.Drawing.Size(180, 21)
        Me.RegularExpressionRadioButton.TabIndex = 1
        Me.RegularExpressionRadioButton.Text = "&Regular Expression"
        '
        'TextRadioButton
        '
        Me.TextRadioButton.Checked = True
        Me.TextRadioButton.Location = New System.Drawing.Point(7, 7)
        Me.TextRadioButton.Name = "TextRadioButton"
        Me.TextRadioButton.Size = New System.Drawing.Size(46, 21)
        Me.TextRadioButton.TabIndex = 0
        Me.TextRadioButton.TabStop = True
        Me.TextRadioButton.Text = "&Text"
        '
        'SearchNowButton
        '
        Me.SearchNowButton.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.SearchNowButton.Location = New System.Drawing.Point(7, 458)
        Me.SearchNowButton.Name = "SearchNowButton"
        Me.SearchNowButton.Size = New System.Drawing.Size(80, 20)
        Me.SearchNowButton.TabIndex = 8
        Me.SearchNowButton.Text = "&Search Now"
        '
        'StopSearchButton
        '
        Me.StopSearchButton.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.StopSearchButton.Location = New System.Drawing.Point(113, 458)
        Me.StopSearchButton.Name = "StopSearchButton"
        Me.StopSearchButton.Size = New System.Drawing.Size(80, 20)
        Me.StopSearchButton.TabIndex = 9
        Me.StopSearchButton.Text = "Sto&p Search"
        '
        'ResultsLabel
        '
        Me.ResultsLabel.Location = New System.Drawing.Point(260, 153)
        Me.ResultsLabel.Name = "ResultsLabel"
        Me.ResultsLabel.Size = New System.Drawing.Size(333, 19)
        Me.ResultsLabel.TabIndex = 4
        '
        'ResultsListBox
        '
        Me.ResultsListBox.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.ResultsListBox.HorizontalScrollbar = True
        Me.ResultsListBox.Location = New System.Drawing.Point(260, 170)
        Me.ResultsListBox.Name = "ResultsListBox"
        Me.ResultsListBox.Size = New System.Drawing.Size(333, 147)
        Me.ResultsListBox.TabIndex = 5
        '
        'label4
        '
        Me.label4.Location = New System.Drawing.Point(7, 340)
        Me.label4.Name = "label4"
        Me.label4.Size = New System.Drawing.Size(83, 20)
        Me.label4.TabIndex = 6
        Me.label4.Text = "File C&ontents:"
        '
        'FileContentsRichTextBox
        '
        Me.FileContentsRichTextBox.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
                    Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.FileContentsRichTextBox.HideSelection = False
        Me.FileContentsRichTextBox.Location = New System.Drawing.Point(7, 361)
        Me.FileContentsRichTextBox.Name = "FileContentsRichTextBox"
        Me.FileContentsRichTextBox.ReadOnly = True
        Me.FileContentsRichTextBox.Size = New System.Drawing.Size(586, 90)
        Me.FileContentsRichTextBox.TabIndex = 7
        Me.FileContentsRichTextBox.Text = ""
        '
        'groupBox2
        '
        Me.groupBox2.Controls.Add(Me.RemoveButton)
        Me.groupBox2.Controls.Add(Me.BrowseButton)
        Me.groupBox2.Controls.Add(Me.DisksListBox)
        Me.groupBox2.Location = New System.Drawing.Point(7, 153)
        Me.groupBox2.Name = "groupBox2"
        Me.groupBox2.Size = New System.Drawing.Size(233, 173)
        Me.groupBox2.TabIndex = 3
        Me.groupBox2.TabStop = False
        Me.groupBox2.Text = "&Look in"
        '
        'RemoveButton
        '
        Me.RemoveButton.Enabled = False
        Me.RemoveButton.Location = New System.Drawing.Point(157, 146)
        Me.RemoveButton.Name = "RemoveButton"
        Me.RemoveButton.Size = New System.Drawing.Size(63, 20)
        Me.RemoveButton.TabIndex = 2
        Me.RemoveButton.Text = "R&emove"
        '
        'BrowseButton
        '
        Me.BrowseButton.Location = New System.Drawing.Point(13, 146)
        Me.BrowseButton.Name = "BrowseButton"
        Me.BrowseButton.Size = New System.Drawing.Size(63, 20)
        Me.BrowseButton.TabIndex = 1
        Me.BrowseButton.Text = "Bro&wse..."
        '
        'DisksListBox
        '
        Me.DisksListBox.HorizontalScrollbar = True
        Me.DisksListBox.Location = New System.Drawing.Point(13, 28)
        Me.DisksListBox.Name = "DisksListBox"
        Me.DisksListBox.Size = New System.Drawing.Size(207, 94)
        Me.DisksListBox.Sorted = True
        Me.DisksListBox.TabIndex = 0
        '
        'TheStatusBar
        '
        Me.TheStatusBar.Location = New System.Drawing.Point(0, 490)
        Me.TheStatusBar.Name = "TheStatusBar"
        Me.TheStatusBar.Size = New System.Drawing.Size(599, 19)
        Me.TheStatusBar.TabIndex = 10
        '
        'TheMainMenu
        '
        Me.TheMainMenu.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.FileMenuItem, Me.SearchMenuItem, Me.HelpMenuItem})
        '
        'FileMenuItem
        '
        Me.FileMenuItem.Index = 0
        Me.FileMenuItem.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.FileExitMenuItem})
        Me.FileMenuItem.Text = "&File"
        '
        'FileExitMenuItem
        '
        Me.FileExitMenuItem.Index = 0
        Me.FileExitMenuItem.Text = "E&xit"
        '
        'SearchMenuItem
        '
        Me.SearchMenuItem.Index = 1
        Me.SearchMenuItem.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.SearchFileContentsMenuItem})
        Me.SearchMenuItem.Text = "&Search"
        '
        'SearchFileContentsMenuItem
        '
        Me.SearchFileContentsMenuItem.Index = 0
        Me.SearchFileContentsMenuItem.Shortcut = System.Windows.Forms.Shortcut.F3
        Me.SearchFileContentsMenuItem.Text = "&Search File Contents"
        '
        'HelpMenuItem
        '
        Me.HelpMenuItem.Index = 2
        Me.HelpMenuItem.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.HelpAboutMenuItem, Me.VisitOurWebSiteMenuItem, Me.menuItem3, Me.HelpOnRegularExpressionsMenuItem})
        Me.HelpMenuItem.Text = "&Help"
        '
        'HelpAboutMenuItem
        '
        Me.HelpAboutMenuItem.Index = 0
        Me.HelpAboutMenuItem.Text = "&About..."
        '
        'VisitOurWebSiteMenuItem
        '
        Me.VisitOurWebSiteMenuItem.Index = 1
        Me.VisitOurWebSiteMenuItem.Text = "&Visit our Web Site"
        '
        'menuItem3
        '
        Me.menuItem3.Index = 2
        Me.menuItem3.Text = "-"
        '
        'HelpOnRegularExpressionsMenuItem
        '
        Me.HelpOnRegularExpressionsMenuItem.Index = 3
        Me.HelpOnRegularExpressionsMenuItem.Text = "Help on Regular E&xpressions"
        '
        'MainForm
        '
        Me.AcceptButton = Me.SearchNowButton
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(599, 509)
        Me.Controls.Add(Me.TheStatusBar)
        Me.Controls.Add(Me.groupBox2)
        Me.Controls.Add(Me.FileContentsRichTextBox)
        Me.Controls.Add(Me.label4)
        Me.Controls.Add(Me.ResultsListBox)
        Me.Controls.Add(Me.ResultsLabel)
        Me.Controls.Add(Me.StopSearchButton)
        Me.Controls.Add(Me.SearchNowButton)
        Me.Controls.Add(Me.groupBox1)
        Me.Controls.Add(Me.FileNameTextBox)
        Me.Controls.Add(Me.label1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Menu = Me.TheMainMenu
        Me.Name = "MainForm"
        Me.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show
        Me.Text = "File Search"
        Me.groupBox1.ResumeLayout(False)
        Me.panel1.ResumeLayout(False)
        Me.groupBox2.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

    <STAThread()> _
    Shared Sub Main()
        Dim MF As EnhMainForm = New EnhMainForm
        AddHandler Application.Idle, AddressOf MF.OnIdle
        Application.Run(MF)
    End Sub

    Public Sub OnIdle(ByVal sender As Object, ByVal e As EventArgs)
        Dim Index As Integer = DisksListBox.SelectedIndex
        Dim SelectedText As String = ""
        If Index >= 0 Then
            SelectedText = DisksListBox.Items(Index).ToString
        End If
        RemoveButton.Enabled = (Index >= 0 AndAlso Not (SelectedText.Length = 3)) AndAlso Not InProgress
        SearchNowButton.Enabled = Not InProgress
        StopSearchButton.Enabled = InProgress
        BrowseButton.Enabled = Not InProgress
        DisksListBox.Enabled = Not InProgress
        FileNameTextBox.Enabled = Not InProgress
        ContainingTextBox.Enabled = Not InProgress
        RegularExpressionRadioButton.Enabled = Not InProgress
        TextRadioButton.Enabled = Not InProgress
        CaseSensitiveCheckBox.Enabled = Not InProgress
        SearchFileContentsMenuItem.Enabled = FileContentsRichTextBox.TextLength > 0
        Dim Text As String = "Res&ults:  (" + ResultsListBox.Items.Count.ToString + ")"
        If Not (String.Compare(ResultsLabel.Text, Text) = 0) Then
            ResultsLabel.Text = Text
        End If
    End Sub

    Private Sub LoadDisksListBox()
        Dim Ch As Char = "A"c
        While Ch <= "Z"c
            Dim Dir As String = Ch + ":\"
            If Directory.Exists(Dir) Then
                DisksListBox.Items.Add(Dir, False)
            End If
            Ch = Chr(Asc(Ch) + 1)
        End While
    End Sub

    Private Sub LoadSettings()
        SerializeConfiguration.LoadSettings()
        FileNameTextBox.Text = SerializeConfiguration.m_Configuration.SearchForText
        ContainingTextBox.Text = SerializeConfiguration.m_Configuration.ContainingText
        TextRadioButton.Checked = SerializeConfiguration.m_Configuration.Text
        RegularExpressionRadioButton.Checked = Not SerializeConfiguration.m_Configuration.Text
        CaseSensitiveCheckBox.Checked = SerializeConfiguration.m_Configuration.CaseSensitive
        For Each Disk As String In SerializeConfiguration.m_Configuration.CheckedDisks
            Dim Index As Integer = DisksListBox.FindString(Disk)
            If Index >= 0 Then
                DisksListBox.SetItemCheckState(Index, CheckState.Checked)
            End If
        Next
        For Each PI As Configuration.PathInfo In SerializeConfiguration.m_Configuration.Paths
            DisksListBox.Items.Add(PI.Path, PI.Checked)
        Next
    End Sub

    Private Sub MainForm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Cursor.Current = Cursors.WaitCursor
        LoadDisksListBox()
        LoadSettings()
        MinimumSize = Size
        Cursor.Current = Cursors.Arrow
    End Sub

    Delegate Sub UpdateStatusBarDelegate(ByVal Text As String)

    Private Sub UpdateStatusBar(ByVal Text As String)
        TheStatusBar.Text = Text
    End Sub

    Private Sub Search()
        Dim USBD As UpdateStatusBarDelegate = AddressOf UpdateStatusBar
        Invoke(USBD, New Object() {"Searching..."})
        InProgress = True
        Dim Cancelled As Boolean = False
        Try
            For Each Dir As String In Dirs
                FileUtils.GetFiles(Dir, SearchPattern, ContainingText, RegularExpression, CaseSensitive, Me)
            Next
        Catch generatedExceptionVariable0 As Exception
            Cancelled = True
        Finally
            InProgress = False
            Invoke(USBD, New Object() {Microsoft.VisualBasic.IIf(Cancelled, "Search cancelled", "Search completed")})
        End Try
    End Sub

    Private Sub SearchNowButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SearchNowButton.Click
        ResultsListBox.Items.Clear()
        FileContentsRichTextBox.Text = ""
        SearchPattern = FileNameTextBox.Text.Trim
        If SearchPattern.Length = 0 Then
            SearchPattern = "*.*"
        End If
        ResultsListBox.Items.Clear()
        ContainingText = ContainingTextBox.Text.Trim
        CaseSensitive = CaseSensitiveCheckBox.Checked
        RegularExpression = RegularExpressionRadioButton.Checked
        Dirs.Clear()
        For Each Index As Integer In DisksListBox.CheckedIndices
            Dim Dir As String = DisksListBox.Items(Index).ToString
            Dirs.Add(Dir)
        Next
        SearchThread = New Thread(AddressOf Search)
        SearchThread.Start()
    End Sub

    Private Sub ResultsListBox_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ResultsListBox.SelectedIndexChanged
        Monitor.Enter(ResultsListBox)
        Dim Index As Integer = ResultsListBox.SelectedIndex
        If Index >= 0 Then
            Cursor.Current = Cursors.WaitCursor
            Dim FileName As String = ResultsListBox.Items(Index).ToString
            Dim eError As Boolean
            Dim Text As String = FileUtils.GetFileText(FileName, eError)
            FileContentsRichTextBox.Text = ""
            If Not eError Then
                FileContentsRichTextBox.Text = Text
            End If
            Cursor.Current = Cursors.Arrow
        End If
        Monitor.Exit(ResultsListBox)
    End Sub

    Private Sub AddPath(ByVal Path As String)
        Dim Found As Boolean = False
        Path = Path.Trim
        For Each S As String In DisksListBox.Items
            If String.Compare(S, Path, True) = 0 Then
                Found = True
            End If
        Next
        If Not Found Then
            DisksListBox.Items.Add(Path, True)
            Dim Disk As String = Directory.GetDirectoryRoot(Path)
            Dim Index As Integer = DisksListBox.FindString(Disk)
            If Index >= 0 Then
                DisksListBox.SetItemCheckState(Index, CheckState.Unchecked)
            End If
        End If
    End Sub

    Private Sub BrowseButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BrowseButton.Click
        Dim F As BrowseForFolderForm = New BrowseForFolderForm("")
        If F.ShowDialog = DialogResult.OK Then
            AddPath(BrowseForFolderForm.m_FolderPath)
        End If
        F.Dispose()
    End Sub

    Private Sub RemoveButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RemoveButton.Click
        Dim Index As Integer = DisksListBox.SelectedIndex
        DisksListBox.Items.RemoveAt(Index)
        If Index >= DisksListBox.Items.Count Then
            System.Math.Max(System.Threading.Interlocked.Decrement(Index), Index + 1)
        End If
        DisksListBox.SelectedIndex = Index
    End Sub

    Private Sub StopSearchButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles StopSearchButton.Click
        If InProgress AndAlso Not (SearchThread Is Nothing) Then
            SearchThread.Abort()
        End If
    End Sub

    Private Sub SaveSettings()
        SerializeConfiguration.m_Configuration.SearchForText = FileNameTextBox.Text.Trim
        SerializeConfiguration.m_Configuration.ContainingText = ContainingTextBox.Text.Trim
        SerializeConfiguration.m_Configuration.Text = TextRadioButton.Checked
        SerializeConfiguration.m_Configuration.CaseSensitive = CaseSensitiveCheckBox.Checked
        SerializeConfiguration.m_Configuration.CheckedDisks.Clear()
        For Each Index As Integer In DisksListBox.CheckedIndices
            Dim Disk As String = DisksListBox.Items(Index).ToString
            SerializeConfiguration.m_Configuration.CheckedDisks.Add(Disk)
        Next
        SerializeConfiguration.m_Configuration.Paths.Clear()
        Dim i As Integer = 0
        While i < DisksListBox.Items.Count
            Dim Path As String = DisksListBox.Items(i).ToString
            If Path.Length > 3 Then
                SerializeConfiguration.m_Configuration.Paths.Add(New Configuration.PathInfo(Path, DisksListBox.GetItemChecked(i)))
            End If
            System.Math.Min(System.Threading.Interlocked.Increment(i), i - 1)
        End While
        SerializeConfiguration.SaveSettings()
    End Sub

    Private Sub MainForm_Closing(ByVal sender As System.Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles MyBase.Closing
        SaveSettings()
        If InProgress AndAlso Not (SearchThread Is Nothing) Then
            SearchThread.Abort()
        End If
    End Sub

    Private Sub RegularExpressionsHelpButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RegularExpressionsHelpButton.Click
        Try
            System.Diagnostics.Process.Start("http://msdn.microsoft.com/library/default.asp?url=/library/en-us/cpguide/html/cpconcomregularexpressions.asp")
        Catch generatedExceptionVariable0 As Exception
        End Try
    End Sub

    Private Sub HelpOnRegularExpressionsMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles HelpOnRegularExpressionsMenuItem.Click
        RegularExpressionsHelpButton_Click(Nothing, Nothing)
    End Sub

    Private Sub VisitOurWebSiteMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles VisitOurWebSiteMenuItem.Click
        Try
            System.Diagnostics.Process.Start("http://www.PersonalMicroCosms.com")
        Catch generatedExceptionVariable0 As Exception
        End Try
    End Sub

    Private Sub HelpAboutMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles HelpAboutMenuItem.Click
        Dim AF As AboutForm = New AboutForm
        AF.ShowDialog()
        AF.Dispose()
    End Sub

    Private Sub FileExitMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles FileExitMenuItem.Click
        Close()
    End Sub

    Public Delegate Sub AddListBoxItemDelegate(ByVal Text As String)

    Public Sub AddListBoxItem(ByVal Text As String)
        ResultsListBox.Items.Add(Text)
    End Sub

    Private Sub SearchFileContentsMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SearchFileContentsMenuItem.Click
        If m_SearchAndReplaceForm Is Nothing OrElse m_SearchAndReplaceForm.IsDisposed Then
            m_SearchAndReplaceForm = New SearchAndReplaceForm(Me, False)
        End If
        m_SearchAndReplaceForm.Left = Form.ActiveForm.Left + (Form.ActiveForm.Width - m_SearchAndReplaceForm.Width) / 2
        m_SearchAndReplaceForm.Top = Form.ActiveForm.Top + (Form.ActiveForm.Height - m_SearchAndReplaceForm.Height) / 2
        m_SearchAndReplaceForm.Activate()
        m_SearchAndReplaceForm.Show()
    End Sub
    Private WM_ACTIVATEAPP As Integer = 28

    Protected Overloads Overrides Sub WndProc(ByRef m As System.Windows.Forms.Message)
        MyBase.WndProc(m)
        If m.Msg = WM_ACTIVATEAPP Then
            If m.WParam.ToInt32 = 0 Then
                If Not (m_SearchAndReplaceForm Is Nothing) AndAlso Not m_SearchAndReplaceForm.IsDisposed Then
                    m_SearchAndReplaceForm.TopLevel = False
                End If
            Else
                If Not (m_SearchAndReplaceForm Is Nothing) AndAlso Not m_SearchAndReplaceForm.IsDisposed Then
                    m_SearchAndReplaceForm.TopLevel = True
                    Me.Activate()
                End If
            End If
        End If
    End Sub
End Class
