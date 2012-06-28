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
        static int speed = 3;
        //                  speed = {     0,     1,     2,     3,     4,     5} 
        static int[] sleepSeconds = { 38200, 32200, 25700, 19400, 13100, 12400 };

        static void Main(string[] args)
        {
            BaRobotDriverDllCSharp.BaRobot brw = new BaRobotDriverDllCSharp.BaRobot();
            brw.SetMode(BaRobotDriverDllCSharp.Constants.TransferMode.COM);
            brw.SetComport(3);
            string[] STORE = { "00;15;120;140;120;90", "00;165;25;90;150;130","00;165;90;160;180;30" };
            speed = brw.GetSpeed();

            while (true)
            {
                Console.Write("Input : ");
                String temp = Console.ReadLine();
                String output = String.Empty;
                DateTime start = DateTime.Now;
                speed = brw.GetSpeed();
                Console.WriteLine("Read Speed is: " + speed.ToString());
                switch (temp)
                {
                    case "exit":
                        break;
                    case "DEMO":
                        Console.WriteLine("DemoMode Started!!!");
                        DemoMode(brw);
                        break;
                    case "DEMO2":
                        Console.WriteLine("Demo2Mode Started!!!");
                        Demo2Mode(brw);
                        break;
                    case "ON":
                        if (brw.StartCommunication())
                            output = "Device Successfully connected";
                        else
                            output = "Could not connect Device";
                        break;
                    case "STORE":
                        output = brw.StoreCommandList(STORE,STORE.Length);
                        break;
                    case "GET":
                        output = brw.GetCommandList();
                        break;
                    case "OFF":
                        if (brw.StopCommunication())
                            output = "Device Successfully disconnected";
                        else
                            output = "Could not disconnect Device. Was it connected?";
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
                    case "CLS":
                        Console.Clear();
                        break;
                    default:
                        output = brw.SendStringAndGetAnswer(temp);
                        break;
                }

                if (temp == "exit")
                    break;

                if (temp != "CLS" && output != String.Empty)
                    Console.WriteLine("Output: " + output);
            }
        }

        private static void DemoMode(BaRobotDriverDllCSharp.BaRobot brw)
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
            output = brw.SendStringAndGetAnswer(executeCommand).ToString();
            end = DateTime.Now;
            PrintMessage(executeCommand, output, start, end);
            System.Threading.Thread.Sleep(7000);
            executeCommand = "MOVE;0;165;1;90;2;160;3;180;4;30";
            start = DateTime.Now;
            output = brw.SendStringAndGetAnswer(executeCommand).ToString();
            end = DateTime.Now;
            PrintMessage(executeCommand, output, start, end);
            System.Threading.Thread.Sleep(7000);
            executeCommand = "OFF";
            start = DateTime.Now;
            output = brw.StopCommunication().ToString();
            end = DateTime.Now;
            PrintMessage(executeCommand, output, start, end);
        }

        private static void Demo2Mode(BaRobotDriverDllCSharp.BaRobot brw)
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
            output = brw.SendStringAndGetAnswer(executeCommand).ToString();
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
