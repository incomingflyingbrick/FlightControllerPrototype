#include <AccelStepper.h>

class StepMotor
{

public:
    StepMotor(int dirPin, int pulsePin, int upLimit, int downLimit);
    void extend();
    void retract();
    void runSpeed();

private:
    AccelStepper *stepper;
    int dirPin;
    int pulsePin;
    int enablePin;
    int upLimit;
    int downLimit;
};