#include "StepMotor.h"
#include <AccelStepper.h>
#include <Arduino.h>


StepMotor::StepMotor(int dirPin, int pulsePin, int upLimit, int downLimit){
    this.pulsePin = pulsePin;
    this.dirPin = dirPin;
    this.upLimit = upLimit;
    this.downLimit = downLimit;
    stepper = AccelStepper(1,this.pulsePin,this,dirPin);
    stepper->setMaxSpeed(2000);
}


void StepMotor::extend(){
    stepper->setSpeed(-1000);
}

void StepMotor::retract(){
    stepper->setSpeed(-1000);
}

void StepMotor::runSpeed(){
    if(digitalRead(this.upLimit)==LOW||digitalRead(this.downLimit)==LOW){
        stepper->stop();
        return;
    }
    stepper->runSpeed();
}


