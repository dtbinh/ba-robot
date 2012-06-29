using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Management;

namespace BaRobotDriverDllCSharp
{
    public class BaRobot
    {
        int transferMode = -1;
        int comport = -1;
        int baudrate = 57600;
        int speed = -1;
        bool isValidTransferMode = false;
        bool isConnected = false;
        System.IO.Ports.SerialPort serialPort = new System.IO.Ports.SerialPort();

        public BaRobot() : this(Constants.TransferMode.COM)
        {
        }

        public BaRobot(int TransferMode, int port = -1)
        {
            comport = port;
            transferMode = TransferMode;
            isValidTransferMode = false;
            isConnected = false;
            baudrate = 57600;
            speed = 3;
        }

        public void SetMode(int TransferMode)
        {
            transferMode = TransferMode;
            if (isConnected)
            {
                StopCommunication();
            }

            if (transferMode == Constants.TransferMode.USB)
            {
                int test = GetUsbDeviceComport("Ba-Robot");
                comport = test;
                if (comport != 0)
                {
                    isValidTransferMode = true;
                    serialPort = new System.IO.Ports.SerialPort("COM" + comport.ToString(), baudrate);
                }
            }
            else if (transferMode == Constants.TransferMode.COM)
            {
                isValidTransferMode = false;
                comport = 0;
            }
            else
            {
                isValidTransferMode = false;
                transferMode = Constants.TransferMode.COM;
                comport = -1;
                serialPort = new System.IO.Ports.SerialPort();
            }
        }

        public void SetComport(int Port)
        {
            if (Port > 0 && Port < 21 && transferMode == Constants.TransferMode.COM)
            {
                comport = Port;
                isValidTransferMode = true;
                serialPort = new System.IO.Ports.SerialPort("COM" + comport.ToString(), baudrate);
            }
            else
            {
                comport = -1;
            }
        }

        public int GetComport()
        {
            return comport;
        }

        public bool StartCommunication()
        {
            SendString("ON");
            return isConnected;
        }

        public bool StopCommunication()
        {
            if (isConnected)
            {
                String retval = SendString("OFF");
                if (retval == "OFF")
                {
                    isConnected = false;
                }
            }
            return !isConnected;
        }

        public int GetSpeed()
        {
            AskSpeed();
            return speed;
        }

        public String SendStringAndGetAnswer(String message)
        {
            return SendString(message);
        }

        public String GetCommandList()
        {
            String message = "GET";
            String answer = SendString(message);
            String retVal = String.Empty;

            int numberCommands = 0;

            try
            {
                numberCommands = Convert.ToInt32(answer);
            }
            catch (Exception e)
            {
                return answer;
            }
            
            if (numberCommands <= 0)
                return "Nothing Stored";

            // NumberCommands@
            retVal += numberCommands.ToString() + "@";

            message = "ACK";

            // NumberCommands@Anzahl Servos@
            retVal = ConcatCommands(message, retVal);

            // NumberCommands@Anzahl Servos@Speed@
            retVal = ConcatCommands(message, retVal);

            for (int i = 0; i < numberCommands; i++)
            {
                // NumberCommands@Anzahl Servos@Speed@command1@command2@...
                retVal = ConcatCommands(message, retVal);
            }

            // NumberCommands@Anzahl Servos@Speed@command1@command2@...@FINISHED
            retVal = ConcatCommands(message, retVal);

            return retVal;
        }

        public String StoreCommandList(String[] CommandList)
        {
            return StoreCommandList(CommandList, CommandList.Length);
        }

        public String StoreCommandList(String[] CommandList, int Count)
        {
            String message = "STORE";
            String answer = SendString(message);
            String retVal = String.Empty;

            if (answer != "ACK")
                return answer;

            message = Count.ToString();
            answer = SendString(message);

            if (answer != "ACK")
                return answer;

            for (int i = 0; i < Count; i++)
            {
                answer = SendString(CommandList[i]);
            }

            return "Finished Saving...";
        }

        public String EraseCommandList()
        {
            String message = "ERASE";
            String retVal = String.Empty;
            
            retVal = SendString(message);

            System.Threading.Thread.Sleep(300);

            message = "ACK";

            retVal += SendString(message);

            return retVal;
        }

        public String OpenGripper()
        {
            String message = "OPEN_GRIPPER";
            String retVal = SendString(message);
            return retVal;
        }

        public String CloseGripper()
        {
            String message = "CLOSE_GRIPPER";
            String retVal = SendString(message);
            return retVal;
        }

        public override string ToString()
        {
            string retval = "BaRobot: Communication: ";
	        if (transferMode == Constants.TransferMode.COM)
	        {
		        retval += "COM, ";
		        retval += "PORT: " + comport.ToString() + ",";
		        retval += "Connected: ";
		        if (isConnected)
			        retval += "yes";
		        else
			        retval += "no";
	        }
	        else
            {
		        retval += "USB, ";
                retval += "(virtuell COM: Port: " + comport.ToString() + "), ";
                retval += "Connected: ";
                if (isConnected)
                    retval += "yes";
                else
                    retval += "no";
            }

	        return retval;
        }

        #region Private Methods

        private String SendString(String message)
        {
            if (isValidTransferMode && message.Length < 200 && (isConnected || message == "ON" || message.StartsWith("SPEED")))
            {
                if (!isConnected && message == "ON")
                    isConnected = true;

                return communicateRS232(message);

            }
            else if (!isConnected)
                return "Not Connected...";
            else
                return "No Valid TransferMode...";
        }

        private void AskSpeed()
        {
            string Speed = SendString("SPEED?");
            try
            {
                speed = Convert.ToInt32(Speed);
            }
            catch (Exception e)
            {
                speed = 3;
            }
        }

        private string communicateRS232(string message)
        {
            serialPort.Open();
            string retval = String.Empty;

            if (serialPort.IsOpen)
            {
                serialPort.WriteLine(message);

                int timer = 0;

                System.Threading.Thread.Sleep(250);

                while (serialPort.BytesToRead == 0)
                {
                    System.Threading.Thread.Sleep(10);
                    timer++;
                    if (timer > 15)
                        break;
                }


                retval = serialPort.ReadExisting();

                serialPort.Close();
                return retval;
            }
            return "Error opening the serial line...";
        }

        private int GetUsbDeviceComport(string usbName)
        {
            string caption = String.Empty;

            if (FindFirstDeviceByCaption(usbName, ref caption))
            {
                if (!String.IsNullOrEmpty(caption) && caption.ToLower().Contains("com"))
                {
                    string temp = caption.Substring(caption.IndexOf("COM") + 3, 1);
                    int tempInt = 0;
                    try
                    {
                        tempInt = Convert.ToInt32(temp);
                    }
                    catch
                    {
                        // nothing to do here
                    }

                    return tempInt;
                }
                else
                    return 0;
            }
            else
                return 0;
            // throw new NotImplementedException();
        }

        private bool FindFirstDeviceByCaption(string deviceCaption, ref string caption)
        {
            string scope = "root\\CIMV2";
            string query = String.Format("SELECT * FROM Win32_PnPEntity WHERE Caption like '%{0}%'", deviceCaption);
            string query2 = String.Format("SELECT * FROM Win32_PnPEntity WHERE Description='{0}'", deviceCaption);
            using (ManagementObjectSearcher objectSearcher =
            new ManagementObjectSearcher(scope, query))
            {
                foreach (ManagementObject managementObject in objectSearcher.Get())
                {
                    foreach (PropertyData property in managementObject.Properties)
                    {
                        // Eigenschaften des gefundenen Gerätes anzeigen
                        if (property.Name.ToLower().Equals("caption"))
                        {
                            caption = property.Value.ToString();
                            break;
                        }
                    }
                    return true;
                }
                return false;
            }
        }

        private String ConcatCommands(String message, String retVal)
        {
            String answer = SendString(message);
            return retVal + answer + "@";
        }

        #endregion

    }
}
