Imports System
Imports System.Collections.Specialized
Imports System.IO
Imports System.Text.RegularExpressions
Imports System.Windows.Forms
Imports System.Threading

    Public Class FileUtils

        Private Sub New()
        End Sub
        Private Shared m_RegularExpression As Regex

    Private Shared Sub GetFiles(ByVal RootDir As String, ByVal Dir As String, ByVal FileTypes As String(), ByVal Text As String, ByVal RegularExpression As Boolean, ByVal CaseSensitive As Boolean, ByVal TheForm As MainForm)
        Dim ALBID As MainForm.AddListBoxItemDelegate = New MainForm.AddListBoxItemDelegate(AddressOf TheForm.AddListBoxItem)
        Try
            For Each FileType As String In FileTypes
                For Each File As String In Directory.GetFiles(Dir, FileType)
                    If FileContainsText(File, Text, RegularExpression, CaseSensitive) Then
                        TheForm.Invoke(ALBID, New Object() {File})
                    End If
                Next
            Next
        Catch generatedExceptionVariable0 As Exception
        End Try
        Try
            For Each D As String In Directory.GetDirectories(Dir)
                GetFiles(RootDir, D, FileTypes, Text, RegularExpression, CaseSensitive, TheForm)
            Next
        Catch generatedExceptionVariable0 As Exception
        End Try
    End Sub

    Public Shared Sub GetFiles(ByVal Dir As String, ByVal SearchPattern As String, ByVal Text As String, ByVal RegularExpression As Boolean, ByVal CaseSensitive As Boolean, ByVal TheForm As MainForm)
        If RegularExpression Then
            Dim Options As RegexOptions = RegexOptions.Compiled
            If Not CaseSensitive Then
                Options = Options Or (RegexOptions.IgnoreCase)
            End If
            m_RegularExpression = New Regex(Text, Options)
        Else
            m_RegularExpression = Nothing
        End If
        Dim FileTypesDelim As Regex = New Regex(",")
        Dim FileTypes As String() = FileTypesDelim.Split(SearchPattern)
        If FileTypes.Length = 0 Then
            FileTypes = New String(1) {}
            FileTypes(0) = ""
        End If
        Dim i As Integer = 0
        While i < FileTypes.Length
            FileTypes(i) = FileTypes(i).Trim
            System.Math.Min(System.Threading.Interlocked.Increment(i), i - 1)
        End While
        GetFiles(Dir, Dir, FileTypes, Text, RegularExpression, CaseSensitive, TheForm)
    End Sub

    Public Shared Function GetFileText(ByVal FileName As String, ByRef eError As Boolean) As String
        Dim Text As String = ""
        Dim FI As FileInfo = New FileInfo(FileName)
        Dim FS As FileStream = Nothing
        Dim SR As StreamReader = Nothing
        eError = False
        Try
            FS = FI.OpenRead
            SR = New StreamReader(FS)
        Catch generatedExceptionVariable0 As System.IO.IOException
            If Not (FS Is Nothing) Then
                FS.Close()
            End If
            If Not (SR Is Nothing) Then
                SR.Close()
            End If
            eError = True
        End Try
        If Not eError Then
            Text = SR.ReadToEnd
            SR.Close()
            FS.Close()
        End If
        Return Text
    End Function

    Public Shared Function FileContainsText(ByVal FileName As String, ByVal Text As String, ByVal RegularExpression As Boolean, ByVal CaseSensitive As Boolean) As Boolean
        Dim Result As Boolean = Text.Length = 0
        If Not Result Then
            Dim eError As Boolean
            Dim AllText As String = GetFileText(FileName, eError)
            If Not eError Then
                If RegularExpression Then
                    Result = m_RegularExpression.IsMatch(AllText)
                Else
                    If Not CaseSensitive Then
                        AllText = AllText.ToUpper
                        Text = Text.ToUpper
                    End If
                    Result = Not (AllText.IndexOf(Text) = -1)
                End If
            End If
        End If
        Return Result
    End Function
End Class