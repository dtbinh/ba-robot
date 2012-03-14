#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <EEPROM.h>
#include "StringArray.h"

// von main
extern String inputString;
extern boolean stringComplete;

// Serial Event liest Daten von der Serial Line
void serialEvent();
// handelt eingelesenen String ab (switch(commands))
void handleSerialCommands();
// Substringt den eingelesenen String
StringArray GetCommandList(String inputstr);
// Debug Printing on Serial1
void DebugPrint(String message);
// Versucht den aktuellen String in Int umzuwandeln
int GetIntFromString(String Value);
// führt das SerialEvent innerhalb des Loops durch //TODO: hier Timer setzen
void WaitForMessage();
// Resetet den Input von Serial
void ResetMessage();

#endif // _FUNCTIONS_H


