Imports System
Imports System.Collections

<Serializable()> _
Public Class Configuration
    Public SearchForText As String = ""
    Public ContainingText As String = ""
    Public Text As Boolean = False
    Public CaseSensitive As Boolean = False
    Public CheckedDisks As ArrayList = New ArrayList

    <Serializable()> _
    Public Class PathInfo

        Public Sub New(ByVal Path As String, ByVal Checked As Boolean)
            Me.Path = Path
            Me.Checked = Checked
        End Sub
        Public Path As String
        Public Checked As Boolean
    End Class
    Public Paths As ArrayList = New ArrayList

    Public Sub New()
    End Sub
End Class