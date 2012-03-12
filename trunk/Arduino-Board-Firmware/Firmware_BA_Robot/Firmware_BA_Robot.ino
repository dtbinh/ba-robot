
#include <EEPROM.h>
#include "Functions.h"

String inputString = "";
boolean stringComplete = false;

// Initializing Routine
void setup() {      
  for (int i = 0; i < 20; i++)
    EEPROM.write(i,0x00);

  Serial.begin(9600);
  #ifdef DEBUG
    Serial1.begin(9600);
  #endif
  inputString.reserve(10000);
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

