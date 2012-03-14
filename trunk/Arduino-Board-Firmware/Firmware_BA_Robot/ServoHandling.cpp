#include "ServoHandling.h"

Servo robotServos[SERVOCOUNT];

void Servos_Init()
{
  for (int i = 0; i < SERVOCOUNT; i++)
  {
    robotServos[i].attach(FIRSTPIN - i);
    Move_Servo(i,MIDPOS);
  }
}

void Move_Servo(StringArray commandList)
{
  String retVal = commandList.GetString(0);
  int servo = 0;
  int speed = 0;
  int value = 0;
  
  if (GetIntFromString(commandList.GetString(1)) != -1)
    servo = GetIntFromString(commandList.GetString(1));
  if (GetIntFromString(commandList.GetString(2)) != -1)
    speed = GetIntFromString(commandList.GetString(2));
  if (GetIntFromString(commandList.GetString(3)) != -1)
    value = GetIntFromString(commandList.GetString(3));

  if (servo >= 0 && servo < SERVOCOUNT && speed != 0 && value != 0)
    Serial.print("Servomovement: OKAY");
  else
  {
    Serial.print("Servomovement: ERROR|");
    Serial.print(servo);
    Serial.print("|");
    Serial.print(speed);
    Serial.print("|");
    Serial.print(value);
    Serial.print("|");
  }
}

void Move_Servo(int servo, int degree)
{
  if (servo >= SERVOCOUNT)
    return;
    
  if (servo == SERVOGRIPPER)
  {
    if (degree > 90)
      degree = 180;
    else
      degree = 0;
  }
  robotServos[servo].write(degree);
}
