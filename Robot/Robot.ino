#include "lasers.h"
#include "motors.h"

Lasers lasers;
Motors motors;
//Lights lights;
bool turnedLeft = false;
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

  //  lights.set(LIGHT_LEFT, (lasers.getLeft() == OUT_OF_RANGE));
  //  lights.set(LIGHT_FRONT, (lasers.getFront() == OUT_OF_RANGE));
  //  lights.set(LIGHT_RIGHT, (lasers.getRight() == OUT_OF_RANGE));

  if (lasers.getDirectFront() >= 200) {
    if (lasers.getDirectLeft() == OUT_OF_RANGE  && !turnedLeft)
    {
      if (!turnedLeft)
      {
        motors.forward();
        delay(400);
        motors.stop();
        if (lasers.getDirectLeft() == OUT_OF_RANGE)
        {
          motors.stop();
          delay(2000);
          motors.left();
          delay(320);
          turnedLeft = true;
          motors.forward();
          delay(1000);
          motors.stop();
        }
      }
    }
    else if (lasers.getDirectLeft() == OUT_OF_RANGE && lasers.getDirectRight() != OUT_OF_RANGE && lasers.getDirectRight() > 100)
    {
      motors.wallRight();
    }
    else if (lasers.getDirectRight() == OUT_OF_RANGE && lasers.getDirectLeft() != OUT_OF_RANGE && lasers.getDirectLeft() > 100 )
    {
      motors.wallLeft();
    }
    else
    {
      motors.forward_adjusting();
    }
  }
  else if (lasers.getRight() == OUT_OF_RANGE) {
    motors.right();
    delay(100);
    Serial.println(motors.getState());
    motors.stop();
  }
  else if (lasers.getLeft() == OUT_OF_RANGE)
  {
    motors.left();
    delay(100);
    Serial.println(motors.getState());
    motors.stop();
  }
  else
  {
    motors.right();
    delay(100);
    Serial.println(motors.getState());
    motors.stop();
  }

  /*else {
    motors.backward();
    }*/

  Serial.print("Motor state: ");
}
