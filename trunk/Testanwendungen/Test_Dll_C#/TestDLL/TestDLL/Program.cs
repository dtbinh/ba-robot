using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace TestDLL
{
    class Program
    {
        static void Main(string[] args)
        {
            // BaRobotLibrary.BaRobot robot = new BaRobotLibrary.BaRobot();
            BaRobotLibrary.BaRobot robot = new BaRobotLibrary.BaRobot();
            string temp2 = robot.ToString();
            BaRobotLibrary.BaRobotWrapper brw = new BaRobotLibrary.BaRobotWrapper();
            brw.SetMode(BaRobotLibrary.TransferMode.COM);
            brw.SetComPort(10);

            while (true)
            {
                Console.Write("Input : ");
                String temp = Console.ReadLine();
                if (temp == "exit")
                    break;

                String output = brw.SendString(temp);
                Console.WriteLine("Output: " + output);
            }
            /*
            String temp = brw.SendString("ON");
            Console.WriteLine(temp);
            Console.ReadKey();
            temp = brw.SendString("OFF");
            Console.WriteLine(temp);
            Console.ReadKey();
            temp = brw.SendString("READ");
            Console.WriteLine(temp);
            Console.ReadKey();
            */
        }
    }
}
