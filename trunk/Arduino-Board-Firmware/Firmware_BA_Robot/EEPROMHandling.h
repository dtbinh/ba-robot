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
// Gives the MOVE;1;xx;2;yy... back
String GetCommandWithServoNumber(int index);
// Get the Count of Commands stored
int GetAnzahlBefehle();
// Get the Value of Speed
int GetSpeed();
// Set the Value of Speed
void SaveSpeed(int);

#endif // _EEPROMHANDLING_H

