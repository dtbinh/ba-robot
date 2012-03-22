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
            brw.SetComPort(7);
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
                    default:
                        output = brw.SendString(temp);
                        break;
                }
                temp2 = brw.ToString();
                if (temp == "exit")
                    break;

                Console.WriteLine("Start: " + start);
                Console.WriteLine("Output: " + output);
                Console.WriteLine("Duration: " + (DateTime.Now - start));
                Console.WriteLine("End: " + DateTime.Now);

#if DEBUG
                Console.Write(temp2);
#endif
            }
        }
    }
}
