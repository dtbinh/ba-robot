using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

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
        static void Main(string[] args)
        {
            // BaRobotLibrary.BaRobot robot = new BaRobotLibrary.BaRobot();
            BaRobotLibrary.BaRobotWrapper brw = new BaRobotLibrary.BaRobotWrapper();
            brw.SetMode(BaRobotLibrary.TransferMode.USB);
            brw.SetMode(BaRobotLibrary.TransferMode.COM);
            brw.SetComPort(3);
            string temp2= brw.ToString();
            string[] STORE = { "00;01;02;03;04;05", "16;17;18;19;20;21" };

#if DEBUG
            Console.Write(temp2);
#endif
            // String test = brw.GetCommand(0);
            while (true)
            {
                Console.Write("Input : ");
                String temp = Console.ReadLine();
                String output = String.Empty;
                DateTime start = DateTime.Now;
                switch (temp)
                {
                    case "exit":
                        break;
                    case "DEMO":
                        Console.WriteLine("DemoMode Started!!!");
                        DemoMode(brw);
                        break;
                    case "ON":
                        output = brw.StartCommunication().ToString();
                        break;
                    case "STORE":
                        output = brw.StoreCommandList(STORE,2);
                        break;
                    case "GET":
                        output = brw.GetCommandList();
                        break;
                    case "OFF":
                        output = brw.StopCommunication().ToString();
                        break;
                    case "ERASE":
                        output = brw.EraseCommandList();
                        break;
                    case "OPEN":
                        output = brw.OpenGripper();
                        break;
                    case "CLOSE":
                        output = brw.CloseGripper();
                        break;
                    default:
                        output = brw.SendString(temp);
                        break;
                }
                temp2 = brw.ToString();
                if (temp == "exit")
                    break;

                // Console.WriteLine("Start: " + start);
                Console.WriteLine("Output: " + output);
                // Console.WriteLine("Duration: " + (DateTime.Now - start));
                // Console.WriteLine("End: " + DateTime.Now);

#if DEBUG
                Console.Write(temp2);
#endif
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
            System.Threading.Thread.Sleep(14000);
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
