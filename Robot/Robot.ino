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

  //Check if the side measurements are close to each other if they are move forward and stop correction
  float ratio = lasers.getLeft() / (float)lasers.getRight();
   Serial.println(ratio,3);
  //if ratio is within 10% we are all good
  //if ratio is 0.5: Right is far away from the wall correct right
  //if ratio is 1.5: Left is far away from wall correct left
  
  if (ratio >= 0.85 && ratio <= 1.15)
  {
    motors.forward();
  }
  else if (ratio >= 1.5 && (lasers.getLeft() != OUT_OF_RANGE && lasers.getRight() != OUT_OF_RANGE))
  {
    motors.adjust_left();
  }
  else if (ratio <= 0.5 && (lasers.getLeft() != OUT_OF_RANGE && lasers.getRight() != OUT_OF_RANGE))
  {
    motors.adjust_right();
  }

//  if (lasers.getFront() == OUT_OF_RANGE) {
//    motors.forward();
//  }
//  else if (lasers.getLeft() == OUT_OF_RANGE) {
//    motors.left();
//  }
//  else if (lasers.getRight() == OUT_OF_RANGE) {
//    motors.right();
//  }
//  else {
//    motors.backward();
//  }
//
  Serial.print("Motor state: ");
  Serial.println(motors.getState());

  delay(100);
}
