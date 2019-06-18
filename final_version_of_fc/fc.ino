#include <Wire.h>
#include "Solenoid.h"

Solenoid s1(40);

void setup()
{
    
}
// for plane X axis is PITCH, Y is ROll, Z is yaw

void loop()
{
    s1.openValve();
    delay(1000);
    s1.closeValve();
    delay(1000);
}
