using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using Con = System.Console;

namespace TestDLL
{
    public static class StringFunctions
    {
        public static string[] ToSeperatedString(this string s, string sep)
        {
            string[] array = new string[] { sep };
            return s.Split(array, StringSplitOptions.None);
        }
    }
    
    class Program
    {
        static int speed          = 3;
        //                  speed = {     0,     1,     2,     3,     4,     5} 
        static int[] sleepSeconds = { 38200, 32200, 25700, 19400, 13100, 12400 };
        static string[] STORE     = { "00;15;120;140;120;90", "00;165;25;90;150;130", "00;165;90;160;180;30" };
        static int usedCom        = 1;

        static void Main(string[] args)
        {   
            BaRobotLibrary.BaRobotWrapper brw = new BaRobotLibrary.BaRobotWrapper();
            brw.SetMode(BaRobotLibrary.TransferMode.COM);
            brw.SetComPort(usedCom);

            string input = "e";
            do
            {
                Con.Clear();
                Con.WriteLine("Eingabe: ");
                Con.WriteLine("1: Turn Robot on ");
                Con.WriteLine("2: Turn Robot off");
                Con.WriteLine("3: Send String ");
                Con.WriteLine("4: STORE ");
                Con.WriteLine("5: GET ");
                Con.WriteLine("6: ERASE ");
                Con.WriteLine("7: Demo Mode");
                Con.WriteLine("8: Change Comport. Current Used: " + usedCom);
                Con.WriteLine("e: Exit ");
                Con.WriteLine("Additional Input: CLS, OPEN, CLOSE");
                Con.Write("Your choice: ");
                input = Con.ReadLine();
                handleCommmands(input, brw);

            } while (input != "e");
        }

        private static void handleCommmands(string input, BaRobotLibrary.BaRobotWrapper brw)
        {
            DateTime start = DateTime.Now;
            string output = String.Empty;
            switch (input)
            {
                case "1":
                    if (brw.StartCommunication())
                        output = "Device Successfully connected";
                    else
                        output = "Could not connect Device";
                    break;
                case "2":
                    if (brw.StopCommunication())
                        output = "Device Successfully disconnected";
                    else
                        output = "Could not disconnect Device. Was it connected?";
                    break;
                case "3":
                    //TODO: Sendstring
                    break;
                case "4":
                    output = brw.StoreCommandList(STORE, STORE.Length);
                    break;
                case "5":
                    output = brw.GetCommandList();
                    break;
                case "6":
                    output = brw.EraseCommandList();
                    break;
                case "7":
                    Console.WriteLine("Demo2Mode Started!!!");
                    Demo2Mode(brw);
                    break;
                case "8":
                    changeComport(brw);
                    break;
                case "e":
                    break;
                case "OPEN":
                    output = brw.OpenGripper();
                    break;
                case "CLOSE":
                    output = brw.CloseGripper();
                    break;
                case "CLS":
                    Console.Clear();
                    break;
                default:
                    output = brw.SendString(input);
                    speed = brw.GetSpeed();
                    break;
            }
            Con.WriteLine(output);
            Con.Write("Press any key...");
            Con.ReadKey();
        }

        private static void changeComport(BaRobotLibrary.BaRobotWrapper brw)
        {
            string comp = String.Empty;
            Con.Write("Comport Number: ");
            comp = Con.ReadLine();
            try
            {
                int temp = Convert.ToInt32(comp);
                brw.SetComPort(temp);
                usedCom = temp;
            }
            catch (Exception e)
            {
                Con.WriteLine(e.ToString());
            }
        }

        private static void DemoMode(BaRobotLibrary.BaRobotWrapper brw)
        {
            String executeCommand = "ON";
            DateTime end = DateTime.Now;
            DateTime start = DateTime.Now;
            String output = brw.StartCommunication().ToString();
            end = DateTime.Now;
            PrintMessage(executeCommand, output, start, end);
            System.Threading.Thread.Sleep(sleepSeconds[speed]);
            executeCommand = "MOVE;0;15;1;120;2;140;3;120;4;90";
            start = DateTime.Now;
            output = brw.SendString(executeCommand).ToString();
            end = DateTime.Now;
            PrintMessage(executeCommand, output, start, end);
            System.Threading.Thread.Sleep(7000);
            executeCommand = "MOVE;0;165;1;90;2;160;3;180;4;30";
            start = DateTime.Now;
            output = brw.SendString(executeCommand).ToString();
            end = DateTime.Now;
            PrintMessage(executeCommand, output, start, end);
            System.Threading.Thread.Sleep(7000);
            executeCommand = "OFF";
            start = DateTime.Now;
            output = brw.StopCommunication().ToString();
            end = DateTime.Now;
            PrintMessage(executeCommand, output, start, end);
        }

        private static void Demo2Mode(BaRobotLibrary.BaRobotWrapper brw)
        {
            String executeCommand = "ON";
            DateTime end = DateTime.Now;
            DateTime start = DateTime.Now;
            String output = String.Empty;
            if (brw.StartCommunication())
                output = "Device Successfully connected";
            else
                output = "Could not connect Device";
            end = DateTime.Now;
            PrintMessage(executeCommand, output, start, end);
            System.Threading.Thread.Sleep(sleepSeconds[speed]);
            
            executeCommand = "LISTPOS;0;1;2";
            start = DateTime.Now;
            output = brw.SendString(executeCommand).ToString();
            end = DateTime.Now;
            PrintMessage(executeCommand, output, start, end);
            System.Threading.Thread.Sleep(15000);
            
            executeCommand = "OFF";
            start = DateTime.Now;
            if (brw.StopCommunication())
                output = "Device Successfully disconnected";
            else
                output = "Could not disconnect Device. Was it connected?";
            end = DateTime.Now;
            PrintMessage(executeCommand, output, start, end);
        }

        private static void PrintMessage(String executeCommand, String output)
        {
            Console.WriteLine("Command was: " + executeCommand);
            Console.WriteLine("Received: " + output);
            // Console.WriteLine("Start: " + start);
            // Console.WriteLine("End: " + DateTime.Now);
            // Console.WriteLine("Duration: " + (DateTime.Now - start));
        }

        private static void PrintMessage(String executeCommand, String output, DateTime start, DateTime end)
        {
            Console.WriteLine("Command was: " + executeCommand);
            Console.WriteLine("Received: " + output);
            Console.WriteLine("Start: " + start);
            Console.WriteLine("End: " + end);
            Console.WriteLine("Duration: " + (end - start));
        }
    }
}
