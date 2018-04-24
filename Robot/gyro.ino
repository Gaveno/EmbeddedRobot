#include <Wire.h>
#include <TimerOne.h>
 
#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C
 
#define GYRO_FULL_SCALE_250_DPS 0x00 
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18
 
#define ACC_FULL_SCALE_2_G 0x00 
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data){
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
   
  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
  Data[index++]=Wire.read();
}

void setup() {
  Wire.begin();
  Serial.begin(9600);

}

long lastTime = millis();
float angularPos = 0;

void loop() {
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);
  int currentTime = millis();

  // Gyroscope
  int16_t gz=Buf[12]<<8 | Buf[13];
  //Serial.println(gz);

  if(abs(gz) > 200)
    angularPos += (float)(gz)*(float)(currentTime - lastTime)/1000;
  Serial.println(angularPos);
  lastTime = currentTime;
  //delay(100);

}
