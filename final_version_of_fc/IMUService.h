class IMUService
{
  public:
    float freeFallThreshold = 0.2;
    bool freeFallDetection(float gForceX, float gForceY, float gForceZ);
};
