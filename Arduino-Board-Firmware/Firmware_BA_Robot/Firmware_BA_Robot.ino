
#include <EEPROM.h>
#include "Functions.h"

// #include "ServoMotor.h"
// ServoMotor servo[8];

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

