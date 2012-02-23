
#include "ServoMotor.h"

ServoMotor servo[8];
// Initializing Routine
void setup() {      
  for (int i = 0; i < 8; i++)
  {  
    servo[i] = ServoMotor();
  }
}

void loop() {

}
