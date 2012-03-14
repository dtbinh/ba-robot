#ifndef _EEPROMHANDLING_H
#define _EEPROMHANDLING_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// von main
extern String inputString;
extern boolean stringComplete;

#include <EEPROM.h>
#include "StringArray.h"

// Movement List speichern
boolean SaveToEEPROM();
// Movement List auslesen
void LoadFromEEPROM();
// Alles löschen
void ClearEEPROM();

#endif // _EEPROMHANDLING_H
