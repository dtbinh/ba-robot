#include "Functions.h"
#include "EEPROMHandling.h"

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

  DebugPrint("Command was: ");
  DebugPrint(commandList.GetString(0));

  // Switch Robot On
  if (commandList.GetString(0) == "ON")
  {
    digitalWrite(13,HIGH);
    Serial.print(commandList.GetString(0)); 
  }
  // Switch Robot Off
  else if (commandList.GetString(0) == "OFF")
  {
    digitalWrite(13,LOW);
    Serial.print(commandList.GetString(0)); 
  } 
  // Store Movement List
  else if (commandList.GetString(0) == "STORE")
  {
    SaveToEEPROM();
  }
  // Retrieve Movement List  
  else if (commandList.GetString(0) == "GET")
  {
    // Serial.print("get");
    LoadFromEEPROM();
  }
  // Erase Movement List
  else if (commandList.GetString(0) == "ERASE")
  {
    ClearEEPROM();
  }  
  // READ Specified EEPROM Address
  else if (commandList.GetString(0) == "READ")
  {
    String temp = "";
    if (commandList.GetElementCount() > 1)
      temp = commandList.GetString(1);
    else
      temp = "0";

    int test = GetIntFromString(temp);

    byte data = EEPROM.read(test);
    String outputstring = commandList.GetString(0) + ": [" + commandList.GetString(1) + "]: " + String(data,HEX) + "\0";

    Serial.print(outputstring);    
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
#ifdef DEBUG
  Serial1.println(message);
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


