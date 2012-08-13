Module Module1

    Dim speed As Int32 = 3
    '                     speed = {    0,     1,     2,     3,     4,     5} 
    Dim sleepSeconds() As Int32 = {38200, 32200, 25700, 19400, 13100, 12400}
    Dim STORE() As String = {"00;15;120;140;120;90", "00;165;25;90;150;130", "00;165;90;160;180;30"}
    Dim usedCom As Int32 = 1

    Sub Main()
        Dim brw As New BaRobotLibrary.BaRobotWrapper()
        brw.SetMode(BaRobotLibrary.TransferMode.COM)
        brw.SetComPort(usedCom)
        Dim input As String = ""

        Do Until input = "e"
            Console.Clear()
            Console.WriteLine("Eingabe: ")
            Console.WriteLine("1: Turn Robot on ")
            Console.WriteLine("2: Turn Robot off")
            Console.WriteLine("3: Send String ")
            Console.WriteLine("4: STORE ")
            Console.WriteLine("5: GET ")
            Console.WriteLine("6: ERASE ")
            Console.WriteLine("7: Demo Mode")
            Console.WriteLine("8: Change Comport. Current Used: " + usedCom.ToString())
            Console.WriteLine("e: Exit ")
            Console.WriteLine("Additional Input: CLS, OPEN, CLOSE")
            Console.Write("Your choice: ")
            input = Console.ReadLine()
            handleCommmands(input, brw)
        Loop

    End Sub

    Private Sub handleCommmands(ByVal input As String, ByVal brw As BaRobotLibrary.BaRobotWrapper)
        Dim start As DateTime = DateTime.Now
        Dim output As String = String.Empty

        Select Case (input)
            Case "1"
                If brw.StartCommunication() Then
                    output = "Device Successfully connected"
                Else
                    output = "Could not connect Device"
                End If
            Case "2"
                If brw.StopCommunication() Then
                    output = "Device Successfully disconnected"
                Else
                    output = "Could not disconnect Device. Was it connected?"
                End If
            Case "3"
                ' Todo: Sendstring
            Case "4"
                output = brw.StoreCommandList(STORE, STORE.Length)
            Case "5"
                output = brw.GetCommandList()
            Case "6"
                output = brw.EraseCommandList()
            Case "7"
                Console.WriteLine("Demo2Mode Started!!!")
                DemoMode(brw)
            Case "8"
                changeComport(brw)
            Case "OPEN"
                output = brw.OpenGripper()
            Case "CLOSE"
                output = brw.CloseGripper()
            Case "CLS"
                Console.Clear()
            Case Else
                output = brw.SendString(input)
                speed = brw.GetSpeed()
        End Select

        Console.WriteLine(output)
        Console.Write("Press any key...")
        Console.ReadKey()
    End Sub

    Private Sub changeComport(ByVal brw As BaRobotLibrary.BaRobotWrapper)
        Dim comp As String = String.Empty
        Console.Write("Comport Number: ")
        comp = Console.ReadLine()
        Try
            Dim temp As Int32 = Convert.ToInt32(comp)
            brw.SetComPort(temp)
            usedCom = temp
        Catch ex As Exception
            Console.WriteLine(ex.ToString())
        End Try
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
