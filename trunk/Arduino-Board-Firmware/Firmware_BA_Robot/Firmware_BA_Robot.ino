// Arduino Libraries must be included here first
#include <EEPROM.h>
#include <Servo.h>
#include "Constants.h"

// Globale Variablen
String  INPUT_STRING               = "";
boolean IS_INPUT_STRING_COMPLETE   = false;
// Stufen von 0 - 5
int     GLOBAL_SERVO_SPEED         = 3;
boolean GLOBAL_BA_ROBOT_DEBUG      = true;
boolean GLOBAL_IS_CONNECTED        = false;
// Servo servo;

// Initializing Routine
void setup() {      
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  INPUT_STRING.reserve(200);
  if (GLOBAL_BA_ROBOT_DEBUG)
  {
    Serial1.begin(115200);
    Serial1.println("Start BA_ROBOT_DEBUG");
  }
  DebugPrint("Setup Done...");
  DebugPrint("Waiting for Message from User...");
  // Servos_Init();
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
      if (GLOBAL_IS_CONNECTED || INPUT_STRING == "ON")
        handleSerialCommands();
        
      ResetMessage();
    }
  }
  // delay(500);
}

