#ifndef _SERVOHANDLING_H
#define _SERVOHANDLING_H

#include <Servo.h>
#include "StringArray.h"
#include "Functions.h"

#define SERVOCOUNT  5
#define SERVOSTARTSPEED  127
#define FIRSTPIN  12 // DownCounting -> Arduino Mega has PWM from 0 - 13
#define SERVOGRIPPER 0
#define MIDPOS 127

void Servos_Init();
void Move_Servo(StringArray commandList);
void Move_Servo(int servo, int degree);

#endif // _SERVOHANDLING_H