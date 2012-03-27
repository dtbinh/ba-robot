#include "ServoHandling.h"
void DriveToNormalPos();

Servo robotServos[SERVOCOUNT];

void Servos_Init()
{
  DebugPrint("Function Servos_Init()");
  DriveToNormalPos();
  for (int i = 0; i < SERVOCOUNT; i++)
  {
    DebugPrint("Attached Servo: #" + String(i) + " to PIN" + String(FIRSTPIN + i) );
    robotServos[i].attach(FIRSTPIN + i);
    // Move_Servo(i,MIDPOS);
  }
  // DriveToNormalPos();
}

void Servos_Release()
{
  DebugPrint("Function Servos_Release()");
  DriveToNormalPos();

  for (int i = 0; i < SERVOCOUNT; i++)
  {
    DebugPrint("Dettached Servo: #" + String(i) + " from PIN" + String(FIRSTPIN + i) );
    robotServos[i].detach();
  }
}

void Move_Servo(StringArray commandList)
{
  DebugPrint("Function Move_Servo(StringArray)");
  String retVal = commandList.GetString(0);
  int servo = -1;
  int value = -1;

  if (GetIntFromString(commandList.GetString(1)) != -1)
    servo = GetIntFromString(commandList.GetString(1));
  if (GetIntFromString(commandList.GetString(2)) != -1)
    value = GetIntFromString(commandList.GetString(2));

  if (servo >= 0 && servo < SERVOCOUNT && value >= 0 && commandList.GetElementCount() > 1)
  {
    DebugPrint("Servomovement: OKAY");
    Move_Servo(servo, value);
  }
  else
  {
    DebugPrint("Servomovement: ERROR|" + String(servo) + "|" + String(value) + "|");
  }
}

void Move_Servo(int servo, int degree)
{
  DebugPrint("Function Move_Servo(int, int)");
  if (servo >= SERVOCOUNT)
    return;

  if (servo == SERVOGRIPPER)
  {
    /*
    if (degree > 90)
      degree = 170;
    else
      degree = 10;

    robotServos[servo].write(degree);
    */
    DebugPrint(String("USE GRIPPER_OPEN Command"));
    PrintMessage(String("USE GRIPPER_OPEN Command"));
    return;
  }

  int oldValue = robotServos[servo].read();

  if (oldValue <= degree)
  {
    for (int i = oldValue; i <= degree; i++)
    {
      robotServos[servo].write(i);
      DebugPrint("Delay: " + String(10 * (5 - GLOBAL_SERVO_SPEED)));
      delay(10 * (5 - GLOBAL_SERVO_SPEED));
      // int compare = robotServos[servo].read();
      // long duration = pulseIn(servo,HIGH);
      // int test = analogRead(servo);
      // int val = map(test, 0, 1023, 0, 179); 
      // int ms = robotServos[servo].readMicroseconds() ;
      // DebugPrint("Read from Servo: " + String(compare) + " analog read: " + String(test) + " gemapped: " + String(val) + "microseconds: " + String(ms));
      // DebugPrint("Read from Servo: " + String(compare));
      /*
      if (i != compare)
      {
        robotServos[servo].write(i-3);
        degree = i - 3;
        break;
      }
      */
    }
  }
  else
  {
    for (int i = oldValue; i >= degree; i--)
    {
      robotServos[servo].write(i);
      DebugPrint("Delay: " + String(10 * (5 - GLOBAL_SERVO_SPEED)));
      delay(10 * (5 - GLOBAL_SERVO_SPEED));
      // int compare = robotServos[servo].read();
      // int test = analogRead(servo);
      // int val = map(test, 0, 1023, 0, 179); 
      // int ms = robotServos[servo].readMicroseconds() ;
      // DebugPrint("Read from Servo: " + String(compare) + " analog read: " + String(test) + " gemapped: " + String(val) + "microseconds: " + String(ms));
      // DebugPrint("Read from Servo: " + String(compare));
      /*
      if (i != compare)
      {
        robotServos[servo].write(i+3);
        degree = i + 3;
        break;
      }
      */
    }
  }
  DebugPrint(String("Wrote to Servo: #") + String(servo) + String(" Value: ") + String(degree));
  PrintMessage(String("Wrote to Servo: #") + String(servo) + String(" Value: ") + String(degree));
}

int Get_Servo_Angle(int servo)
{
  if (servo < 0 && servo >= SERVOCOUNT)
    return -1;
    
  return robotServos[servo].read();
}

void Open_Gripper()
{
  robotServos[SERVOGRIPPER].write(15);  
  DebugPrint(String("Wrote to Servo: #") + String(SERVOGRIPPER) + String(" Value: ") + String(15) + " (GRIPPER)");
  PrintMessage(String("Gripper opened..."));
}

void Close_Gripper()
{
  robotServos[SERVOGRIPPER].write(165);  
  DebugPrint(String("Wrote to Servo: #") + String(SERVOGRIPPER) + String(" Value: ") + String(165) + " (GRIPPER)");
  PrintMessage(String("Gripper opened..."));
}

void DriveToNormalPos()
{
  DebugPrint("DriveToNormalPos()");
  DebugPrint("Speed: " + String(GLOBAL_SERVO_SPEED));
  Move_Servo(4,180);
  Move_Servo(3,110);
  Move_Servo(2,160);
  Move_Servo(3,180);
  Move_Servo(4,30);
  Move_Servo(1,60);
  Move_Servo(1,120);
  Move_Servo(1,90);
}
