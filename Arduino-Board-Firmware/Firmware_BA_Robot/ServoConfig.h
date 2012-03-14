#ifndef SERVOCONFIG_H_
#define SERVOCONFIG_H_

class ServoConfig
{
private:
  int valueMax;
  int valueMin;

public:
  ServoConfig();
  ServoConfig(int _max, int _min);
};

#endif // SERVOCONFIG_H_


