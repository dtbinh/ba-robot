#ifndef _SERVOHANDLING_H
#define _SERVOHANDLING_H

#include "Constants.h"

#define SERVOCOUNT  5
#define SERVOSTARTSPEED  127
#define FIRSTPIN  2 // UpCounting -> Arduino Mega has PWM from 2 - 13 (0 and 1 are RX and TX)
#define SERVOGRIPPER 0
#define MIDPOS 90

void Servos_Init();
void Move_Servo(StringArray commandList);
void Move_Servo(int servo, int degree);
int Get_Servo_Angle(int servo);

#endif // _SERVOHANDLING_H
