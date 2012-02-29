#include "ServoConfig.h"

ServoConfig::ServoConfig()
{
  this->valueMax = 0;
  this->valueMin = 0;
}

ServoConfig::ServoConfig(int _max, int _min)
{
  this->valueMax = _max;
  this->valueMin = _min;
}


