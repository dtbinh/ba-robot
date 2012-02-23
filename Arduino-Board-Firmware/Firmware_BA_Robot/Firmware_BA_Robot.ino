
#include "ServoMotor.h"
#include <UsbDevice.h>

ServoMotor servo[8];

// Initializing Routine
void setup() {      
  Serial.begin(9600);
  inputString.reserve(200);
}

void loop() {
  
  
  if (stringComplete) 
  {
    if (inputString == "")
    {
      stringComplete = false;      
    }
    else
    {
      Serial.println(inputString); 
      // clear the string:
      inputString = "";
      stringComplete = false;
    }
  }
}

void serialEvent() 
{
  while (Serial.available()) 
  {
    char inChar = (char)Serial.read(); 
    if (inChar == '\n' || inChar == '\r') {
      stringComplete = true;
    }
    else
    { 
      inputString += inChar;
    } 
  }
}

