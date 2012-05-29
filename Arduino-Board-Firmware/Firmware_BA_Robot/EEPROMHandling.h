#ifndef _EEPROMHANDLING_H
#define _EEPROMHANDLING_H

#include "Constants.h"

// Movement List speichern
boolean SaveToEEPROM();
// Movement List auslesen
void LoadFromEEPROM();
// Alles löschen
void ClearEEPROM();
// Reads command from the given index from eeprom
String GetCommandAt(int index);
String GetCommandWithServoNumber(int index);
int GetAnzahlBefehle();
int GetSpeed();
void SaveSpeed(int);


#endif // _EEPROMHANDLING_H
