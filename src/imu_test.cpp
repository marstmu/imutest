#include <Arduino.h>
#include <Wire.h>
const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
int16_t AccX_raw, AccY_raw, AccZ_raw;

void setup() {
  
  Serial5.begin(9600); // antenna
  Serial.begin(9600); // monitor

  Wire.begin(); //start communication 
  Wire.beginTransmission(MPU);
  
  Wire.write(0x6B);
  Wire.write(0x00); //reset device
  Wire.endTransmission(true);

  delay(100);
}

void loop() {
Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX_raw = (Wire.read() << 8 | Wire.read()); // X-axis value
  AccY_raw = (Wire.read() << 8 | Wire.read()); // Y-axis value
  AccZ_raw = (Wire.read() << 8 | Wire.read()); // Z-axis value

  AccX = (AccX_raw / 16384.0)*9.81; // Convert to actual accelerometer value
  AccY = (AccY_raw / 16384.0)*9.81;
  AccZ = (AccZ_raw / 16384.0)*9.81;

  Serial.print("aX =    ");
  Serial.print(AccX);
     
  Serial.print("    aY =   ");   
  Serial.print(AccY);

  Serial.print("    aZ =   "); 
  Serial.println(AccZ);

  Serial5.print(",");
  Serial5.print(AccX);
  Serial5.print(",");  
  Serial5.print(AccY);
  Serial5.print(",");
  Serial5.println(AccZ);




  delay(100);

}
