#include "ServoMotor.h"

ServoMotor::ServoMotor()
{
  this->value = 0;
  this->speed = 0;
  this->newValue = 0;
  this->speedCounter = 0;
  this->configuration = ServoConfig();
}


