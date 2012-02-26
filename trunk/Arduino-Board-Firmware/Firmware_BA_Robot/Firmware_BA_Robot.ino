
#include "ServoMotor.h"
#include <EEPROM.h>

ServoMotor servo[8];
String inputString = "";
boolean stringComplete = false;
int currentCommandCount = 0;

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
      handleSerialCommands();
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

void handleSerialCommands()
{
  // EEPROM.write(0,0xFF);
  // byte data = EEPROM.read(0);
  // Serial.println(data,HEX);
  // char** temp = SubstringCommandList(inputString);

  /*
  for (int i = 0; i < currentCommandCount; i++)
   {
   String tempString = temp[i];
   Serial.print(tempString); 
   Serial.print("<>"); 
   } 
   */
  // Serial.print(inputString); 
  // clear the string:
  if (inputString == "READ")
  {
    byte data = EEPROM.read(0);
    String temp = String(data,HEX);
    char p[10];
    temp.toCharArray(p,10);
    p[2] = '\0';
    p[3] = 'H';
    p[4] = 'U';    
    temp += "\0";
    String output = temp;
    inputString += temp;
      // Serial.print(inputString); 
    // Serial.print(" ");
    Serial.print(p);
  } 
  else if (inputString == "ON")
  {
    digitalWrite(13,HIGH);
    Serial.print(inputString); 
  }
  else
  {
    digitalWrite(13,LOW);
    Serial.print(inputString); 
  } 
  inputString = "";
  stringComplete = false;
}

char** SubstringCommandList(String inputstr)
{
  Serial.println("Start: ");
  Serial.print(inputString);
  String temp = inputstr;
  int counter = 0;
  while (true)
  {
    if (temp.indexOf(';') == -1)
      break;
    else 
    {
      counter++;
      temp = temp.substring(temp.indexOf(';') + 1);
    }
  }
  currentCommandCount = counter;
  Serial.print(currentCommandCount);

  char* retVal[counter];
  temp = inputstr;

  for (int i = 0; i < counter; i++)
  {
    unsigned int length = (unsigned int)temp.indexOf(';');
    char tempStorage[length];
    temp.substring(0,temp.indexOf(';')).toCharArray(tempStorage, temp.indexOf(';'));
    Serial.println(tempStorage);
    retVal[i] = tempStorage;
    temp = temp.substring(temp.indexOf(';'));
  }
  return retVal;
}


