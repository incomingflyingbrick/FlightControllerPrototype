#include <MadgwickAHRS.h>

class IMUService
{



public:
  float freeFallThreshold = 0.25; // 0.2 g
  bool freeFallDetection(float gForceX, float gForceY, float gForceZ);
  float getRoll();
  float getPitch();
  float getYaw();
  void startFilter(int frequency);
  void setupIMU();
  IMUService(Wire i2cWire);

private:
  Madgwick filter;
  Wire* wire;
};
