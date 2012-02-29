
#include <EEPROM.h>
#include "Functions.h"

String inputString = "";
boolean stringComplete = false;

// Initializing Routine
void setup() {      
  Serial.begin(9600);
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
      handleSerialCommands();
    }
  }
}

