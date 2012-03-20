#include "Functions.h"

void serialEvent() 
{
  while (Serial.available()) 
  {
    char inChar = (char)Serial.read(); 
    if (inChar == '\n' || inChar == '\r') {
      stringComplete = true;
      inputString += '\0';
    }
    else
    { 
      inputString += inChar;
    } 
  }
}

void handleSerialCommands()
{
  StringArray commandList = GetCommandList(inputString);
  String command = commandList.GetString(0);

  DebugPrint("Command was: ");
  DebugPrint(command);

  // RobotControl
  // Switch Robot On
  if (command == "ON")
  {
    digitalWrite(13,HIGH);
    Serial.print(command); 
  }
  // Switch Robot Off
  else if (command == "OFF")
  {
    digitalWrite(13,LOW);
    Serial.print(command); 
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
    // Serial.print("get");
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
  else if (command == "MOVE")
  {
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
    DebugPrint(String("Wrote to Servo: " + commandList.GetString(1)));
    /*
    if (commandList.GetElementCount() >= 4)
     Move_Servo(commandList);
     else
     Serial.print("Error: not enough Arguments, Example MOVE;SERVONUMBER;SPEED;VALUE");
     */
  }
  // Set Speed
  else if (command == "SPEED")
  {
    int newSpeed = GetIntFromString(commandList.GetString(1));
    if (newSpeed >= 0 && newSpeed <= 5)
      GLOBAL_SERVO_SPEED = newSpeed;
  }
  // Other Command
  else
  {
    for (int i = 0; i < commandList.GetElementCount(); i++)
    {
      Serial.print(commandList.GetString(i));
      Serial.print("|");
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

void DebugPrint(String message)
{
#ifdef BA_ROBOT
  Serial1.println("### " + message);
  // Serial.println("### " + message);
#endif
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
  while (! stringComplete)
  {    
    serialEvent();
  }
}

void ResetMessage()
{
  DebugPrint("Resetting InputString"); 
  stringComplete = false;
  inputString = "";
}

void handleReadCommand(StringArray commandList)
{
  String temp = "";
  if (commandList.GetElementCount() > 1)
    temp = commandList.GetString(1);
  else
    temp = "0";

  int test = GetIntFromString(temp);

  byte data = EEPROM.read(test);
  String outputstring = commandList.GetString(1) + ": [" + commandList.GetString(1) + "]: " + String(data,HEX) + "\0";

  Serial.print(outputstring);   
}



