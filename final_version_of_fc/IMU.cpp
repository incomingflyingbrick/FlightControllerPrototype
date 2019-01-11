#include <math.h>

class IMUService{
    public:
        

        bool freeFallDetection(float gForceX, float gForceY, float gForceZ ){
            float totalAccel = sqrt(gForceX)+sqrt(gForceY)+sqrt(gForceZ);
            if(totalAccel<=freeFallThreadHold){
                return true;
            }
            return false;
        }

    private:
        float freeFallThreadHold = 0.25;

};

