class StepMotor
{
public:
    StepMotor(int dirPin,int pulsePin);
    void extend(double distance);
    void retract(double distance);
};