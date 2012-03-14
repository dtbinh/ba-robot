// Arduino Libraries must be included here first
#include <EEPROM.h>
#include <Servo.h>
#include "Functions.h"
#include "ServoHandling.h"

#define DEBUG

String inputString = "";
boolean stringComplete = false;

// Initializing Routine
void setup() {      
#ifdef DEBUG
  Serial1.begin(9600);
#endif
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  Servos_Init();
  inputString.reserve(200);
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
