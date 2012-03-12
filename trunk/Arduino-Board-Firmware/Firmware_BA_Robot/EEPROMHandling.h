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

boolean SaveToEEPROM();
StringArray LoadFromEEPROM();

#endif // _EEPROMHANDLING_H
