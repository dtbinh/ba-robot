// Arduino Libraries must be included here first
#include <EEPROM.h>
#include <Servo.h>
#include "Constants.h"
// #include "ServoHandling.h"

// Servo servo;
String inputString = "";
boolean stringComplete = false;
Servo servo;
int GLOBAL_SERVO_SPEED = 5;

// Initializing Routine
void setup() {      
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  inputString.reserve(200);
#ifdef BA_ROBOT
  Serial1.begin(9600);
  Serial1.println("Start BA_ROBOT_DEBUG");
  Serial.println("Start BA_ROBOT_DEBUG");
#endif
  Serial1.begin(9600);
  Serial1.print("Hallo...");
  DebugPrint("Setup Done...");
  DebugPrint("Waiting for Message from User...");
  servo.attach(2);
  servo.write(90);
// servo.detach();
}

// Main Loop
void loop() {
  Serial1.print("Hallo...");
  // wenn String eingelesen dann abhandeln
  if (stringComplete) 
  {
    if (inputString == "")
    {
      stringComplete = false;     
    }
    else
    {
      DebugPrint("Complete String received: " + inputString);
      handleSerialCommands();
      ResetMessage();
    }
  }
  delay(500);
}

