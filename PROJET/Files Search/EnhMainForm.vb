Imports System

Public Class EnhMainForm
    Inherits MainForm
    Implements ISearchAndReplaceFormParent

    Public Function GetText() As String Implements ISearchAndReplaceFormParent.GetText
        Return FileContentsRichTextBox.Text
    End Function

    Public Sub SetText(ByVal Text As String) Implements ISearchAndReplaceFormParent.SetText
        FileContentsRichTextBox.Text = Text
    End Sub

    Public Sub SetCursorPos(ByVal CursorPos As Integer) Implements ISearchAndReplaceFormParent.SetCursorPos
        FileContentsRichTextBox.Select(CursorPos, 0)
    End Sub

    Public Function GetSelectionStart() As Integer Implements ISearchAndReplaceFormParent.GetSelectionStart
        Return FileContentsRichTextBox.SelectionStart
    End Function

    Public Sub sSelect(ByVal Start As Integer, ByVal Length As Integer) Implements ISearchAndReplaceFormParent.sSelect
        FileContentsRichTextBox.Select(Start, Length)
    End Sub

    Public Function GetTextNotFoundCaption() As String Implements ISearchAndReplaceFormParent.GetTextNotFoundCaption
        Return Text
    End Function

    Public Sub New()
    End Sub

End Class

