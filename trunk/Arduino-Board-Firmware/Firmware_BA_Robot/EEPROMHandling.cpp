#include "EEPROMHandling.h"

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
  PrintMessage("ACK");

  ResetMessage();
  WaitForMessage();
  DebugPrint("Input came: " + INPUT_STRING);

  PrintMessage("ACK");

  int  numberCommands = GetIntFromString(INPUT_STRING);

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
    DebugPrint("Input came: " + INPUT_STRING);
    StringArray temp = GetCommandList(INPUT_STRING);
    SaveCommands(i,temp);
  }
  return true;
}

void LoadFromEEPROM()
{
  // muss als erstes stehen, da ein eeprom read etwas dauert und ansonsten ein timeout erreicht wird
  // Send Anzahl Befehle
  int numberCommands = GetAnzahlBefehle();
  PrintMessage(numberCommands);
  
  DebugPrint("Function LoadFromEEPROM");
  String comparer = String("ACK");

  if (numberCommands == 0)
  {
    return;
  } 

  ResetMessage();
  WaitForMessage();
  DebugPrint("Input came: " + INPUT_STRING);  
  // ACK ?
  if (comparer.compareTo(INPUT_STRING) != 0)
  {
    return;
  }

  // Send Anzahl Servos
  PrintMessage(GetAnzahlServos());
  ResetMessage();
  WaitForMessage();

  DebugPrint("Input came: " + INPUT_STRING); 
  // ACK ?
  if (comparer.compareTo(INPUT_STRING) != 0)
  {
    return;
  }

  // Send Speed
  PrintMessage(GetSpeed());
  ResetMessage();
  WaitForMessage();

  DebugPrint("Input came: " + INPUT_STRING); 
  // ACK ?
  if (comparer.compareTo(INPUT_STRING) != 0)
  {
    return;
  }

  for (int i = 0; i < numberCommands; i++)
  {
    String temp = GetCommandAt(i);  
    PrintMessage(temp);
    ResetMessage();
    WaitForMessage();
    DebugPrint("Input came: " + INPUT_STRING); 
  }

  if (comparer.compareTo(INPUT_STRING) == 0)
    PrintMessage("FINISHED");
  else
    PrintMessage("ERROR");
}

void ClearEEPROM()
{
  DebugPrint("Function ClearEEPROM"); 
  // PrintMessage("\nTrying erase EEPROM...");
  DebugPrint("Trying erase EEPROM...");
  
  /*
   * No Complete Erasin, set CommandCount to zero is enough
  for (int i = 0; i < 4096; i++)
  {
    EEPROM.write(i,0x00);
  }
  */
  SaveAnzahlBefehle(0);
  DebugPrint("Erasing EEPROM done...");
  ResetMessage();
  WaitForMessage();  
  DebugPrint("Input came: " + INPUT_STRING); 
  PrintMessage("Erasing EEPROM done...");
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

