#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#ifndef BA_ROBOT
#define BA_ROBOT
#endif

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <EEPROM.h>
#include <Servo.h>
#include "StringArray.h"
#include "Functions.h"
#include "EEPROMHandling.h"
#include "ServoHandling.h"

extern String inputString;
extern boolean stringComplete;
extern Servo servo;
extern int GLOBAL_SERVO_SPEED;

#endif // _CONSTANTS_H

