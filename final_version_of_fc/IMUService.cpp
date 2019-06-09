#include <math.h>
#include "IMUService.h"
#include <Wire.h>

bool IMUService::freeFallDetection(float gForceX, float gForceY, float gForceZ)
{
    float totalAccel = pow(gForceX,2) + pow(gForceY,2) + pow(gForceZ,2);
    if (sqrt(totalAccel) <= IMUService::freeFallThreshold) //free fall threadhold 0.25g
    {
        return true;
    }
    return false;
}

