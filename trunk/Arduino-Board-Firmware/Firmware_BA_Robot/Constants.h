#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#ifndef BA_ROBOT
#define BA_ROBOT
#endif

// für unterschiedliche Arduino IDE Versionen 
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// EEPROM Funktionsbibliothek
#include <EEPROM.h>
// Servo Funktionsbibliothek
#include <Servo.h>

// Ab hier eigene Bibliotheken
// ein selbstgeschriebenes StringArray als verkettete Liste
#include "StringArray.h"
// benötigte Funktionen
#include "Functions.h"
// Handling des Speicherns und Lesens des EEPROMs
#include "EEPROMHandling.h"
// Handling der Servobewegun
#include "ServoHandling.h"

extern String INPUT_STRING;
extern boolean IS_INPUT_STRING_COMPLETE;
extern int GLOBAL_SERVO_SPEED;
extern boolean GLOBAL_BA_ROBOT_DEBUG;
extern boolean GLOBAL_IS_CONNECTED;

#endif // _CONSTANTS_H

