#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "Constants.h"

// Serial Event liest Daten von der Serial Line
void serialEvent();
// handelt eingelesenen String ab (switch(commands))
void handleSerialCommands();
// Debug Printing on Serial1
void DebugPrint(String message);
// führt das SerialEvent innerhalb des Loops durch //TODO: hier Timer setzen
void WaitForMessage();
// Resetet den Input von Serial
void ResetMessage();
// Versucht den aktuellen String in Int umzuwandeln
int GetIntFromString(String Value);
// Substringt den eingelesenen String
StringArray GetCommandList(String inputstr);
// for Handling the READ Commmand
void handleReadCommand(StringArray commandList);

#endif // _FUNCTIONS_H
