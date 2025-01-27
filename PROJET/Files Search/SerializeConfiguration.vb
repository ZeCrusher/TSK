Imports System
Imports System.IO
Imports System.Runtime.Serialization
Imports System.Runtime.Serialization.Formatters.Binary
Imports System.Windows.Forms

    Public Class SerializeConfiguration

        Private Sub New()
        End Sub
        Public Shared m_Configuration As Configuration = New Configuration

        Private Shared Function GetConfigFilePath() As String
            Return Path.GetDirectoryName(Application.ExecutablePath) + "\config.dat"
        End Function

        Public Shared Sub SaveSettings()
            Dim Write As Stream = Nothing
            Try
                Dim FI As FileInfo = New FileInfo(GetConfigFilePath)
                Write = FI.OpenWrite
                Dim BF As BinaryFormatter = New BinaryFormatter
                BF.Serialize(Write, m_Configuration)
            Catch generatedExceptionVariable0 As Exception
            Finally
                If Not (Write Is Nothing) Then
                    Write.Close()
                End If
            End Try
        End Sub

        Public Shared Sub LoadSettings()
            Dim Read As Stream = Nothing
            Try
                Dim FI As FileInfo = New FileInfo(GetConfigFilePath)
                Read = FI.OpenRead
                Dim BF As BinaryFormatter = New BinaryFormatter
                Dim Tmp As Configuration = CType(BF.Deserialize(Read), Configuration)
                m_Configuration = Tmp
            Catch generatedExceptionVariable0 As Exception
            Finally
                If Not (Read Is Nothing) Then
                    Read.Close()
                End If
            End Try
        End Sub
    End Class