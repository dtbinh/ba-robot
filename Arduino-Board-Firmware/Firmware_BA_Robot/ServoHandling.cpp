#include "ServoHandling.h"

Servo robotServos[SERVOCOUNT];

void Servos_Init()
{
  DebugPrint("Function Servos_Init()");
  for (int i = 0; i < SERVOCOUNT; i++)
  {
    robotServos[i].attach(FIRSTPIN + i);
    Move_Servo(i,MIDPOS);
  }
}

void Move_Servo(StringArray commandList)
{
  DebugPrint("Function Move_Servo(StringArray)");
  String retVal = commandList.GetString(0);
  int servo = 0;
  int value = 0;

  if (GetIntFromString(commandList.GetString(1)) != -1)
    servo = GetIntFromString(commandList.GetString(1));
  if (GetIntFromString(commandList.GetString(2)) != -1)
    value = GetIntFromString(commandList.GetString(2));

  if (servo >= 0 && servo < SERVOCOUNT && value != 0)
  {
    DebugPrint("Servomovement: OKAY");
    Move_Servo(servo, value);
  }
  else
  {
    DebugPrint("Servomovement: ERROR|");
    DebugPrint(String(servo));
    DebugPrint("|");
    DebugPrint(String(value));
    DebugPrint("|");
  }
}

void Move_Servo(int servo, int degree)
{
  DebugPrint("Function Move_Servo(int, int)");
  if (servo >= SERVOCOUNT)
    return;

  if (servo == SERVOGRIPPER)
  {
    if (degree > 90)
      degree = 170;
    else
      degree = 10;

    robotServos[servo].write(degree);
    return;
  }

  int oldValue = robotServos[servo].read();

  if (oldValue <= degree)
  {
    for (int i = oldValue; i <= degree; i++)
    {
      robotServos[servo].write(i);
      delay(10 * (5 - GLOBAL_SERVO_SPEED));
    }
  }
  else
  {
    for (int i = oldValue; i >= degree; i--)
    {
      robotServos[servo].write(i);
      delay(10 * (5 - GLOBAL_SERVO_SPEED));
    }
  }
}

int Get_Servo_Angle(int servo)
{
  if (servo < 0 && servo >= SERVOCOUNT)
    return -1;
    
  return robotServos[servo].read();
}
