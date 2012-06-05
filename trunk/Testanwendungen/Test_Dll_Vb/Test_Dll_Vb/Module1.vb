Module Module1

    Sub Main()
        Dim brw As New BaRobotLibrary.BaRobotWrapper()
        brw.SetMode(BaRobotLibrary.TransferMode.COM)
        brw.SetComPort(3)
        Dim STORE() As String = {"00;15;120;140;120;90", "00;165;90;160;180;30"}

        While (True)
            Console.Write("Input: ")
            Dim temp As String
            temp = Console.ReadLine()
            Dim output As String = ""
            Select Case temp
                Case "exit"
                Case "DEMO"
                    Console.WriteLine("DemoMode started!!!")
                    DemoMode(brw)
                Case "ON"
                    output = brw.StartCommunication().ToString()
                Case "OFF"
                    output = brw.StopCommunication().ToString()
                Case "GET"
                    output = brw.GetCommandList()
                Case "STORE"
                    output = brw.StoreCommandList(STORE, 2)
                Case "OPEN"
                    output = brw.OpenGripper()
                Case "CLOSE"
                    output = brw.CloseGripper()
                Case "ERASE"
                    output = brw.EraseCommandList()
                Case "CLS"
                    Console.Clear()
                Case Else
                    output = brw.SendString(temp)
            End Select

            If temp = "exit" Then
                Exit While
            End If

            If temp <> "CLS" Then
                Console.WriteLine("Output: " + output)
            End If

        End While

    End Sub

    Private Sub DemoMode(ByVal brw As BaRobotLibrary.BaRobotWrapper)
        Dim executeCommand = "ON"
        Dim endTime As DateTime = DateTime.Now
        Dim startTime As DateTime = DateTime.Now
        Dim outputString As String = brw.StartCommunication().ToString()
        endTime = DateTime.Now
        PrintMessage(executeCommand, outputString, startTime, endTime)
        System.Threading.Thread.Sleep(14000)

        executeCommand = "LISTPOS;0;1"
        startTime = DateTime.Now
        outputString = brw.SendString(executeCommand).ToString()
        endTime = DateTime.Now
        PrintMessage(executeCommand, outputString, startTime, endTime)
        System.Threading.Thread.Sleep(14000)

        executeCommand = "OFF"
        startTime = DateTime.Now
        outputString = brw.StopCommunication().ToString()
        endTime = DateTime.Now
        PrintMessage(executeCommand, outputString, startTime, endTime)
    End Sub

    Private Sub PrintMessage(ByVal executeCommand As String, ByVal outputString As String, ByVal startTime As Date, ByVal endTime As Date)
        Console.WriteLine("Command was: " + executeCommand)
        Console.WriteLine("Received: " + outputString)
        Console.WriteLine("Start: " + startTime)
        Console.WriteLine("End: " + endTime)
        Console.WriteLine("Duration: " + "")
    End Sub

End Module
