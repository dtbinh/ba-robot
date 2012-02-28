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

  if (commandList.GetString(0) == "READ")
  {
    /*
    EEPROM.write(0,0xFF);
    EEPROM.write(1,0xFE);
    EEPROM.write(2,0xFD);
    */
    String temp = "";
    if (commandList.GetElementCount() > 1)
      temp = commandList.GetString(1);
    else
      temp = "0";
      
    char tempArray[temp.length() + 1];
    temp.toCharArray(tempArray,temp.length() + 1);
    tempArray[temp.length()] = '\0';
    int test = atoi(tempArray);
    byte data = EEPROM.read(test);
    String outputstring = commandList.GetString(0) + ": [" + commandList.GetString(1) + "]: " + String(data,HEX) + "\0";

    Serial.print(outputstring);    
  } 
  else if (commandList.GetString(0) == "ON")
  {
    digitalWrite(13,HIGH);
    Serial.print(commandList.GetString(0)); 
  }
  else if (commandList.GetString(0) == "OFF")
  {
    digitalWrite(13,LOW);
    Serial.print(commandList.GetString(0)); 
  } 
  else
  {
    for (int i = 0; i < commandList.GetElementCount(); i++)
    {
      Serial.print(commandList.GetString(i));
      Serial.print("|");
    }
  }
  inputString = "";
  stringComplete = false;
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

