#include <math.h>
#include "IMUService.h"

bool IMUService::freeFallDetection(float gForceX, float gForceY, float gForceZ)
{
    float totalAccel = sqrt(gForceX) + sqrt(gForceY) + sqrt(gForceZ);
    if (totalAccel <= 0.25) //free fall threadhold 0.25g
    {
        return true;
    }
    return false;
}
