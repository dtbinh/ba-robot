Module Module1

    Dim speed As Int32 = 3
    '                     speed = {    0,     1,     2,     3,     4,     5} 
    Dim sleepSeconds() As Int32 = {38200, 32200, 25700, 19400, 13100, 12400}

    Sub Main()
        Dim brw As New BaRobotLibrary.BaRobotWrapper()
        brw.SetMode(BaRobotLibrary.TransferMode.COM)
        brw.SetComPort(3)
        Dim STORE() As String = {"00;15;120;140;120;90", "00;165;25;90;150;130", "00;165;90;160;180;30"}

        While (True)
            Console.Write("Input: ")
            Dim temp As String
            temp = Console.ReadLine()
            Dim output As String = ""
            speed = brw.GetSpeed()
            Console.WriteLine("Read Speed is: " + speed.ToString())
            Select Case temp
                Case "exit"
                Case "DEMO"
                    Console.WriteLine("DemoMode started!!!")
                    DemoMode(brw)
                Case "ON"
                    If (brw.StartCommunication()) Then
                        output = "Device Successfully connected"
                    Else
                        output = "Could not connect Device"
                    End If
                Case "OFF"
                    If (brw.StopCommunication()) Then
                        output = "Device Successfully disconnected"
                    Else
                        output = "Could not disconnect Device. Was it connected?"
                    End If
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
        Dim outputString As String
        If (brw.StartCommunication()) Then
            outputString = "Device Successfully connected"
        Else
            outputString = "Could not connect Device"
        End If
        endTime = DateTime.Now
        PrintMessage(executeCommand, outputString, startTime, endTime)
        System.Threading.Thread.Sleep(sleepSeconds(speed))

        executeCommand = "LISTPOS;0;1;2"
        startTime = DateTime.Now
        outputString = brw.SendString(executeCommand).ToString()
        endTime = DateTime.Now
        PrintMessage(executeCommand, outputString, startTime, endTime)
        System.Threading.Thread.Sleep(15000)

        executeCommand = "OFF"
        startTime = DateTime.Now
        If (brw.StopCommunication()) Then
            outputString = "Device Successfully disconnected"
        Else
            outputString = "Could not disconnect Device. Was it connected?"
        End If
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
