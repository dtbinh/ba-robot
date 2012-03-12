#include "EEPROMHandling.h"
#include "Functions.h"

void SaveAnzahlBefehle(int numberCommands);
void SaveAnzahlServos();
void SaveSpeed(int Speed);
void SaveCommands(int currentIndex, StringArray command);

boolean SaveToEEPROM()
{
  Serial.print("ACK");
  stringComplete = false;
  inputString = "";
  
  while (! stringComplete)
  {    
    serialEvent();
  }
  DebugPrint("From SaveToEEPROM: ");
  DebugPrint("Input came: " + stringComplete);
  
  Serial.print("ACK");

  int  numberCommands = GetIntFromString(inputString);
  
  stringComplete = false;
  inputString = "";
  
  if (numberCommands <= 0)
  {
    return false;
  }
  
  SaveAnzahlBefehle(numberCommands);
  SaveAnzahlServos();
  SaveSpeed(127);
  
  for (int i = 0; i < numberCommands; i++)
  {
    while (! stringComplete)
    {    
      serialEvent();
    }
    DebugPrint("From SaveToEEPROM: ");
    DebugPrint("Input came: " + stringComplete);
    StringArray temp = GetCommandList(inputString);
    Serial.print("Test: ");
    Serial.print(temp.GetString(0));
    Serial.print("|");    
    Serial.print(temp.GetStringAsInt(1));
    Serial.print("|");    
    Serial.print(temp.GetStringAsInt(2));
    SaveCommands(i,temp);
    stringComplete = false;
    inputString = "";
  }
  return true;
}

/*
boolean SaveToEEPROM(StringArray commandList)
{
  String temp = "";
  if (commandList.GetElementCount() > 1)
    temp = commandList.GetString(1);
  else
    temp = "0";
      
  char tempArray[temp.length() + 1];
  temp.toCharArray(tempArray,temp.length() + 1);
  tempArray[temp.length()] = '\0';
  int test = atoi(tempArray);
  Serial.print("InputCount: ");
  Serial.print(test);
  
  byte LByte = test;
  byte HByte = (test >> 8 );
  EEPROM.write(0,HByte);
  EEPROM.write(1,LByte);
  Serial.print("HighByte: ");
  temp = String(HByte,HEX);
  Serial.print(temp);  
  Serial.print("\nLowByte: ");
  temp = String(LByte,HEX);
  Serial.print(temp);  
  Serial.print("\nTogether: ");  
  int var = ((HByte << 8 ) | LByte);
  Serial.print(var);  
  return false;
}
*/

StringArray LoadFromEEPROM()
{
  return StringArray();
}

void SaveAnzahlBefehle(int numberCommands)
{
  byte LByte = numberCommands;
  byte HByte = (numberCommands >> 8 );
  EEPROM.write(0,HByte);
  EEPROM.write(1,LByte);
}

void SaveAnzahlServos()
{
  EEPROM.write(2,0x05);
}

void SaveSpeed(int Speed)
{
  EEPROM.write(3,0x7F);
}

void SaveCommands(int currentIndex, StringArray command)
{
  // erste Adresse = 10 und dann weiter mit command + servos
  
  int offset = 10 + (currentIndex * (5 + 1));
  for (int i = 0; i < 6; i++)
  {
    EEPROM.write(offset + i, command.GetStringAsInt(i));
  }
}


