#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <EEPROM.h>
#include "StringArray.h"

extern String inputString;
extern boolean stringComplete;

void serialEvent();
void handleSerialCommands();
StringArray GetCommandList(String inputstr);

#endif
