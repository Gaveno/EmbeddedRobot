/*
 * Control the lasers on the car.
 */

#include <Wire.h>
#include <VL6180X.h>

#include "circulararray.h"

#define RANGE 1

#define OUT_OF_RANGE 255

/* List of adresses for each sensor - after reset the address can be configured */
#define addressLeft 0x20
#define addressFront 0x22
#define addressRight 0x24

/* These Arduino pins must be wired to the IO0 pin of VL6180x */
int enablePinLeft = 3;
int enablePinFront = 4;
int enablePinRight = 5;

/* Create a new instance for each sensor */
VL6180X sensorLeft;
VL6180X sensorFront;
VL6180X sensorRight;


class Lasers {
public:
  Lasers();

  void setup();
  void update();

  byte getLeft();
  byte getFront();
  byte getRight();

private:
  CircularArray<byte> laserLeft;
  CircularArray<byte> laserFront;
  CircularArray<byte> laserRight;
};

Lasers::Lasers() {
  
};

void Lasers::setup() {
  Wire.begin();

  // Reset all connected sensors
  pinMode(enablePinLeft,OUTPUT);
  pinMode(enablePinFront,OUTPUT);
  pinMode(enablePinRight,OUTPUT);
  
  digitalWrite(enablePinLeft, LOW);
  digitalWrite(enablePinFront, LOW);
  digitalWrite(enablePinRight, LOW);
  
  delay(1000);
  
  // sensorLeft
  Serial.println("Start Sensor Left");
  digitalWrite(enablePinLeft, HIGH);
  delay(50);
  sensorLeft.init();
  sensorLeft.configureDefault();
  sensorLeft.setAddress(addressLeft);
  Serial.println(sensorLeft.readReg(0x212),HEX); // read I2C address
  sensorLeft.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensorLeft.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensorLeft.setTimeout(500);
  sensorLeft.stopContinuous();
  sensorLeft.setScaling(RANGE); // configure range or precision 1, 2 oder 3 mm
  delay(300);
  sensorLeft.startInterleavedContinuous(100);
  delay(100);
  
  // sensorFront
  Serial.println("Start Sensor Front");
  digitalWrite(enablePinFront, HIGH);
  delay(50);
  sensorFront.init();
  sensorFront.configureDefault();
  sensorFront.setAddress(addressFront);
  Serial.println(sensorFront.readReg(0x212),HEX);
  sensorFront.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensorFront.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensorFront.setTimeout(500);
  sensorFront.stopContinuous();
  sensorFront.setScaling(RANGE);
  delay(300);
  sensorFront.startInterleavedContinuous(100);
  delay(100);

//  sensorRight
    Serial.println("Start Sensor Right");
    digitalWrite(enablePinRight, HIGH);
    delay(50);
    sensorRight.init();
    sensorRight.configureDefault();
    sensorRight.setAddress(addressRight);
    Serial.println(sensorRight.readReg(0x212),HEX);
    sensorRight.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
    sensorRight.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
    sensorRight.setTimeout(500);
    sensorRight.stopContinuous();
    sensorRight.setScaling(RANGE);
    delay(300);
    sensorRight.startInterleavedContinuous(100);
  
  //delay(1000);
 
  Serial.println("Sensors ready!");
  //delay(3000);
}


void Lasers::update() {
  laserLeft.addValue(sensorLeft.readRangeContinuousMillimeters());
  if (sensorLeft.timeoutOccurred()) { Serial.print("Sensor Left TIMEOUT"); }
  laserFront.addValue(sensorFront.readRangeContinuousMillimeters());
  if (sensorFront.timeoutOccurred()) { Serial.print("Sensor Front TIMEOUT"); }
  laserRight.addValue(sensorRight.readRangeContinuousMillimeters());
  if (sensorRight.timeoutOccurred()) { Serial.print("Sensor Right TIMEOUT"); }
}

byte Lasers::getLeft() {
  return laserLeft.getAverage();  
}

byte Lasers::getFront() {
  return laserFront.getAverage();  
}

byte Lasers::getRight() {
  return laserRight.getAverage();  
}

