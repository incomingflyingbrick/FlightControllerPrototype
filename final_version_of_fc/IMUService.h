#include <MadgwickAHRS.h>

class IMUService
{

public:
  float freeFallThreshold = 0.25; // 0.2 g
  bool freeFallDetection(float gForceX, float gForceY, float gForceZ);
  float getRoll();
  float getPitch();
  float getYaw();
  void setupIMU();
  void loop();
  IMUService();
  unsigned long microsPerReading = 1000000 / 25; // 25Hz 读取数据频率
  unsigned long microsPrevious;

private:
  Madgwick filter;
  void recordGyroRegistersForSetUp();
  int refreshRate = 25;
  void recordAccelRegisters();
  void recordGyroRegisters();
  void processAccelData();
  void processGyroData();
  void printData();
  //accel related variable
  long accelX, accelY, accelZ;
  float gForceX, gForceY, gForceZ;
  //gyro related variable
  long gyro_x_cal, gyro_y_cal, gyro_z_cal;
  long gyroX, gyroY, gyroZ;
  float rotX, rotY, rotZ;
  //oritation related variable
  float roll, pitch, heading;
};
