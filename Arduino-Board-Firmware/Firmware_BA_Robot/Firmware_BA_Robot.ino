
#include <EEPROM.h>
#include "Functions.h"

#define DEBUG

String inputString = "";
boolean stringComplete = false;

// Initializing Routine
void setup() {      
  Serial.begin(9600);
#ifdef DEBUG
  Serial1.begin(9600);
#endif
  inputString.reserve(200);
  pinMode(13, OUTPUT);
}

// Main Loop
void loop() {

  // wenn String eingelesen dann abhandeln
  if (stringComplete) 
  {
    if (inputString == "")
    {
      stringComplete = false;      
    }
    else
    {
      DebugPrint("Complete String received");
      handleSerialCommands();
      ResetMessage();
    }
  }
}

