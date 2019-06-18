#include <math.h>
#include "IMUService.h"
#include <Wire.h>
#include <MadgwickAHRS.h>


IMUService(Wire i2cWire){
    wire = new 
}


bool IMUService::freeFallDetection(float gForceX, float gForceY, float gForceZ)
{
    float totalAccel = pow(gForceX, 2) + pow(gForceY, 2) + pow(gForceZ, 2);
    if (sqrt(totalAccel) <= IMUService::freeFallThreshold) //free fall threadhold 0.25g
    {
        return true;
    }
    return false;
}

float IMUService::getRoll()
{

}
float IMUService::getPitch()
{

}
float IMUService::getYaw()
{

}


void IMUService::startFilter(int frequency){
    setupMPU();
    filter.begin(frequency);

}

void IMUService::setupIMU()
{
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B);                  //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000);            //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B);                  //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
  Wire.write(0x00000000);            //Setting the gyro to full scale +/- 250deg./s
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C);                  //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5)
  Wire.write(0b00000000);            //Setting the accel to +/- 2g
  Wire.endTransmission();
}

