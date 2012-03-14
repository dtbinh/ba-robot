#include "EEPROMHandling.h"
#include "Functions.h"

void SaveAnzahlBefehle(int numberCommands);
void SaveAnzahlServos();
void SaveSpeed(int Speed);
void SaveCommands(int currentIndex, StringArray command);
int GetAnzahlBefehle();
int GetAnzahlServos();
int GetSpeed();
String GetCommandAt(int index);

boolean SaveToEEPROM()
{
  DebugPrint("Function SaveToEEPROM");
  Serial.print("ACK");
  
  ResetMessage();
  WaitForMessage();
  DebugPrint("Input came: " + stringComplete);

  Serial.print("ACK");

  int  numberCommands = GetIntFromString(inputString);

  if (numberCommands <= 0)
  {
    return false;
  }

  SaveAnzahlBefehle(numberCommands);
  SaveAnzahlServos();
  SaveSpeed(127);

  for (int i = 0; i < numberCommands; i++)
  {
    ResetMessage();
    WaitForMessage();
    DebugPrint("Input came: " + stringComplete);
    StringArray temp = GetCommandList(inputString);
    SaveCommands(i,temp);
  }
  return true;
}

void LoadFromEEPROM()
{
  DebugPrint("Function LoadFromEEPROM");
  String comparer = String("ACK");

  // Send Anzahl Befehle
  int numberCommands = GetAnzahlBefehle();

  Serial.print(numberCommands);
  if (numberCommands == 0)
  {
    return;
  } 

  ResetMessage();
  WaitForMessage();
  DebugPrint("Input came: " + stringComplete);  
  // ACK ?
  if (comparer.compareTo(inputString) != 0)
  {
    return;
  }

  // Send Anzahl Servos
  Serial.print(GetAnzahlServos());
  ResetMessage();
  WaitForMessage();

  DebugPrint("Input came: " + stringComplete); 
  // ACK ?
  if (comparer.compareTo(inputString) != 0)
  {
    return;
  }

  // Send Speed
  Serial.print(GetSpeed());
  ResetMessage();
  WaitForMessage();

  DebugPrint("Input came: " + stringComplete); 
  // ACK ?
  if (comparer.compareTo(inputString) != 0)
  {
    return;
  }

  for (int i = 0; i < numberCommands; i++)
  {
    String temp = GetCommandAt(i);  
    Serial.print(temp);
    ResetMessage();
    WaitForMessage();
    DebugPrint("Input came: " + stringComplete); 
  }

  if (comparer.compareTo(inputString) == 0)
    Serial.print("FINISHED");
  else
    Serial.print("ERROR");
}

void ClearEEPROM()
{
  DebugPrint("Function ClearEEPROM"); 
  Serial.print("\nTrying erase EEPROM...");
  for (int i = 0; i < 4096; i++)
  {
    EEPROM.write(i,0x00);
  }
  ResetMessage();
  WaitForMessage();  
  DebugPrint("Input came: " + stringComplete); 
  Serial.print("Erasing EEPROM done...");
}

void SaveAnzahlBefehle(int numberCommands)
{
  byte LByte = numberCommands;
  byte HByte = (numberCommands >> 8 );
  EEPROM.write(0,HByte);
  EEPROM.write(1,LByte);
}

int GetAnzahlBefehle()
{
  byte HByte = EEPROM.read(0);
  byte LByte = EEPROM.read(1);
  if ( (HByte == B00000000) && (LByte == B00000000) )
    return 0;

  return ((HByte << 8 ) | LByte);
}

void SaveAnzahlServos()
{
  EEPROM.write(2,0x05);
}

int GetAnzahlServos()
{
  return EEPROM.read(2);
}

void SaveSpeed(int Speed)
{
  if (Speed < 256)
    EEPROM.write(3,Speed);
  else 
    EEPROM.write(3,0xFF);
}

int GetSpeed()
{
  return EEPROM.read(3);
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

String GetCommandAt(int index)
{
  int offset = 10 + (index * (5 + 1));
  String retVal = "";
  for (int i = 0; i < 6; i++)
  {
    int temp = EEPROM.read(offset + i);
    retVal += temp;
    if (i != 5)
      retVal += ";";
  }

  return retVal;
}




