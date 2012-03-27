#include "Functions.h"

void serialEvent() 
{
  while (Serial.available()) 
  {
    char inChar = (char)Serial.read(); 
    if (inChar == '\n' || inChar == '\r') {
      IS_INPUT_STRING_COMPLETE = true;
      INPUT_STRING += '\0';
    }
    else
    { 
      INPUT_STRING += inChar;
    } 
  }
}

void handleSerialCommands()
{
  DebugPrint("Function handleSerialCommands");
  StringArray commandList = GetCommandList(INPUT_STRING);
  String command = commandList.GetString(0);

  DebugPrint("Command was: " + command);

  // RobotControl
  // Switch Robot On
  if (command == "ON")
  {
    GLOBAL_IS_CONNECTED = true;
    digitalWrite(13,HIGH);
    Servos_Init();
    PrintMessage(command); 
  }
  // Switch Robot Off
  else if (command == "OFF")
  {
    GLOBAL_IS_CONNECTED = false;
    digitalWrite(13,LOW);
    Servos_Release();
    PrintMessage(command); 
  } 
  // EEPROM Handling
  // Store Movement List
  else if (command == "STORE")
  {
    SaveToEEPROM();
  }
  // Retrieve Movement List  
  else if (command == "GET")
  {
    // PrintMessage("get");
    LoadFromEEPROM();
  }
  // Erase Movement List
  else if (command == "ERASE")
  {
    ClearEEPROM();
  }  
  // READ Specified EEPROM Address
  else if (command == "READ")
  {
    handleReadCommand(commandList);
  } 
  // Servohandling
  // Move Servo
  else if (command == "MOVE")
  {
    Move_Servo(commandList);
    /*
    int oldValue = servo.read();
     int newValue = GetIntFromString(commandList.GetString(1));
     
     if (oldValue <= newValue)
     {
     for (int i = oldValue; i <= newValue; i++)
     {
     servo.write(i);
     delay(10 * (5 - GLOBAL_SERVO_SPEED));
     }
     }
     else
     {
     for (int i = oldValue; i >= newValue; i--)
     {
     servo.write(i);
     delay(10 * (5 - GLOBAL_SERVO_SPEED));
     }
     }
     */
    /*
    if (commandList.GetElementCount() >= 4)
     Move_Servo(commandList);
     else
     PrintMessage("Error: not enough Arguments, Example MOVE;SERVONUMBER;SPEED;VALUE");
     */
  }
  // Set Speed
  else if (command == "SPEED")
  {
    int newSpeed = GetIntFromString(commandList.GetString(1));
    if (newSpeed >= 0 && newSpeed <= 5)
    {
      DebugPrint("GLOBAL_SERVO_SPEED  set to: " + String(newSpeed));
      GLOBAL_SERVO_SPEED = newSpeed;
    }
  }
  // Opens the Gripper
  else if (command == "OPEN_GRIPPER")
  {
    Open_Gripper();
  }
  // Closes the Gripper
  else if (command == "CLOSE_GRIPPER")
  {
    Close_Gripper();
  }
  // Other Command
  else
  {
    DebugPrint("Unknown Command");
    for (int i = 0; i < commandList.GetElementCount(); i++)
    {
      PrintMessage(commandList.GetString(i));
      PrintMessage("|");
    }
  }
}

StringArray GetCommandList(String inputstr)
{
  StringArray retVal;

  String temp = inputstr;

  while (true)
  {
    if (temp.indexOf(';') < 0)
    {
      retVal.AddString(temp);  
      break;
    }
    else 
    {
      retVal.AddString(temp.substring(0,temp.indexOf(';')));
      temp = temp.substring(temp.indexOf(';') + 1);
    }
  }
  return retVal;
}
void PrintMessage(String message)
{
  Serial.flush();
  message += "\0";
  Serial.print(message);
}

void PrintMessage(int message)
{
  String msg = String(message);
  msg += "\0";
  Serial.flush();
  Serial.print(msg);
}

void DebugPrint(String message)
{
// #ifdef BA_ROBOT
  if (GLOBAL_BA_ROBOT_DEBUG)
  {
    Serial1.println("### " + message);
    Serial1.flush();
  }
  // Serial.println("### " + message);
// #endif
}

int GetIntFromString(String Value)
{ 
  char tempArray[Value.length() + 1];
  Value.toCharArray(tempArray,Value.length() + 1);
  tempArray[Value.length()] = '\0';
  return atoi(tempArray);
}

void WaitForMessage()
{
  DebugPrint("Waiting for Message...");
  unsigned long startTime = millis();
  unsigned long currentTime = millis();
  while (! IS_INPUT_STRING_COMPLETE)
  {    
    serialEvent();
    if ( currentTime > (startTime + 5000 )) 
    {
      DebugPrint("Expected something but nothing came...");
      break;
    }
    
    currentTime = millis();
  }
}

void ResetMessage()
{
  IS_INPUT_STRING_COMPLETE = false;
  INPUT_STRING = "";
  DebugPrint("INPUT_STRING resetted"); 
}

void handleReadCommand(StringArray commandList)
{
  DebugPrint("Function handleReadCommand"); 
  String temp = "";
  if (commandList.GetElementCount() > 1)
    temp = commandList.GetString(1);
  else
    temp = "0";

  int test = GetIntFromString(temp);

  byte data = EEPROM.read(test);
  String outputstring = commandList.GetString(1) + ": [" + commandList.GetString(1) + "]: " + String(data,HEX) + "\0";

  PrintMessage(outputstring);   
}




