#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include "ServoConfig.h"

class ServoMotor
{
private:
  int value;
  int speed;
  int newValue;
  volatile int speedCounter;
  ServoConfig configuration;

public:
  ServoMotor();
};

#endif // SERVOMOTOR_H_


