class IMUService
{
  public:
    float freeFallThreshold = 0.2; // 0.2 g 
    bool freeFallDetection(float gForceX, float gForceY, float gForceZ);
};
