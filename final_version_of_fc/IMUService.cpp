#include <math.h>
#include "IMUService.h"

bool IMUService::freeFallDetection(float gForceX, float gForceY, float gForceZ)
{
    float totalAccel = sqrt(gForceX) + sqrt(gForceY) + sqrt(gForceZ);
    if (totalAccel <= IMUService::freeFallThreshold) //free fall threadhold 0.25g
    {
        return true;
    }
    return false;
}
