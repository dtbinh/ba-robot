// Arduino Libraries must be included here first
#include <EEPROM.h>
#include <Servo.h>
#include <MemoryFree.h>
#include "Constants.h"

// Globale Variablen
String  INPUT_STRING               = "";
boolean IS_INPUT_STRING_COMPLETE   = false;
// Stufen von 0 - 5
int     GLOBAL_SERVO_SPEED         = 3;
boolean GLOBAL_BA_ROBOT_DEBUG      = true;
boolean GLOBAL_IS_CONNECTED        = false;

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
  int tempSpeed = GetSpeed();
  if ( tempSpeed > 0 && tempSpeed <= 5)
  {
    GLOBAL_SERVO_SPEED = tempSpeed;
    DebugPrint("Speed read from EEPROM: " + String(tempSpeed));
  }
  else
  {
    SaveSpeed(GLOBAL_SERVO_SPEED);
    DebugPrint("Speed initialized and stored to EEPROM: " + String(tempSpeed));
  }
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
      if (GLOBAL_IS_CONNECTED || INPUT_STRING == "ON" || INPUT_STRING.startsWith("SPEED") )
        handleSerialCommands();
        
      if (INPUT_STRING == "OFF")
        software_Reset();
     
      ResetMessage();
    }
    // Serial1.print("freeMemory()=");
    // Serial1.println(freeMemory());
    
  }
}

void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
  asm volatile ("  jmp 0");
}  
