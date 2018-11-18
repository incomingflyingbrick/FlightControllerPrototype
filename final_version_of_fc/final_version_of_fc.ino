#include <Wire.h>
#include <MadgwickAHRS.h>
#include <PID_v1.h>

// make filter for orientation
Madgwick filter;

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;

float roll,pitch,heading;

unsigned long microsPerReading, microsPrevious;// count sample rate

// PID library setup
double SetpointRoll = 0.0;
double InputRoll, OutputRoll;
PID rollPID(&InputRoll, &OutputRoll, &SetpointRoll,0.67,2.5,0.37, DIRECT);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
  filter.begin(25);
  // turn on PID
  rollPID.SetMode(AUTOMATIC);
  rollPID.SetOutputLimits(-360.0,360.0);
  // always at last line
  microsPerReading = 1000000 / 25;
  microsPrevious = micros();
}


void loop() {
  unsigned long microsNow;
  microsNow = micros();
  if(microsNow - microsPrevious >= microsPerReading){
    recordAccelRegisters();
    recordGyroRegisters();
    //printData();
    filter.updateIMU(rotX, rotY, rotZ, gForceX, gForceY, gForceZ);
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();
    InputRoll = roll;
    rollPID.Compute();
    printOritation();
  }
}

//print roll pitch yaw and PID
void printOritation(){
  Serial.print("Roll:");
  Serial.print(roll);
  Serial.print(" Roll PID:");
  Serial.print(OutputRoll);
  Serial.print(" Pitch:");
  Serial.print(pitch);
  Serial.print(" Yaw:");
  Serial.println(heading);
}

// call in setup()
void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 
}

// get accel data
void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}

// process accel data
void processAccelData(){
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;
}

// get gyro data
void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

// process gyro data
void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
}

void printData() {
  Serial.print("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);
  Serial.print(" Accel (g)");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.println(gForceZ);
}
