
#include "ServoMotor.h"

ServoMotor servo[8];
String inputString = "";
boolean stringComplete = false;
// Initializing Routine
void setup() {      
  Serial.begin(9600);
  inputString.reserve(200);
  pinMode(13, OUTPUT);
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
      Serial.print(inputString); 
      
      // clear the string:
      if (inputString == "ON")
        digitalWrite(13,HIGH);
      else
        digitalWrite(13,LOW);
        
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
      inputString += '\0';
    }
    else
    { 
      inputString += inChar;
    } 
  }
}

