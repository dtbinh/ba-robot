#ifndef _SERVOHANDLING_H
#define _SERVOHANDLING_H

#include "Constants.h"

#define SERVOCOUNT  5
#define FIRSTPIN  2 // UpCounting -> Arduino Mega has PWM from 2 - 13 (0 and 1 are RX and TX)
#define SERVOGRIPPER 0
#define MIDPOS 90

// Initialize the Servoos
void Servos_Init();
// Release the Servos
void Servos_Release();
// Move Servo with Commands stored in Commandlist
void Move_Servo(StringArray commandList);
// Move Servo #servo to Value #degree
void Move_Servo(int servo, int degree);
// Opens the Gripper
void Open_Gripper();
// Closes the Gripper
void Close_Gripper();
// Returns the Current Value of the Searched Servo
int Get_Servo_Angle(int servo);

#endif // _SERVOHANDLING_H
