#include "lasers.h"
#include "motors.h"

Lasers lasers;
Motors motors;

void setup()
{
  Serial.begin(9600);

  lasers.setup();
  motors.setup();
}

void loop()
{
  lasers.update();

  // Test Left
  Serial.print("Sensor Left: ");
  Serial.print(lasers.getLeft());

  // Test Front
  Serial.print(" Sensor Front: ");
  Serial.print(lasers.getFront());

  // Test Right
  Serial.print(" Sensor Right: ");
  Serial.print(lasers.getRight());
  Serial.println();

  if (lasers.getFront() == OUT_OF_RANGE) {
    motors.forward();
  }
  else if (lasers.getLeft() == OUT_OF_RANGE) {
    motors.left();
  }
  else if (lasers.getRight() == OUT_OF_RANGE) {
    motors.right();
  }
  else {
    motors.backward();
  }

  Serial.print("Motor state: ");
  Serial.println(motors.getState());
  
  delay(10);
}
