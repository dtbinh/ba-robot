// Arduino Libraries must be included here first
#include <EEPROM.h>
#include <Servo.h>
#include "Constants.h"

// Globale Variablen
String INPUT_STRING = "";
boolean IS_INPUT_STRING_COMPLETE = false;
int GLOBAL_SERVO_SPEED = 5;
boolean GLOBAL_BA_ROBOT_DEBUG = false;
// Servo servo;

// Initializing Routine
void setup() {      
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  INPUT_STRING.reserve(200);
  if (GLOBAL_BA_ROBOT_DEBUG)
  {
    Serial1.begin(9600);
    Serial1.println("Start BA_ROBOT_DEBUG");
  }
  DebugPrint("Setup Done...");
  DebugPrint("Waiting for Message from User...");
  /*
  servo.attach(2);
  servo.write(90);
  servo.detach();
  */
}

// Main Loop
void loop() {
  // wenn String eingelesen dann abhandeln
  if (IS_INPUT_STRING_COMPLETE) 
  {
    if (INPUT_STRING == "")
    {
      IS_INPUT_STRING_COMPLETE = false;     
    }
    else
    {
      DebugPrint("Complete String received: " + INPUT_STRING);
      handleSerialCommands();
      ResetMessage();
    }
  }
  delay(500);
}


