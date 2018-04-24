/*
 * Control the motors of the car.
 */

#ifndef __MOTORS_H__
#define __MOTORS_H__

#include "lasers.h"

extern Lasers lasers;

#define STATE_FORWARD  0
#define STATE_LEFT     1
#define STATE_RIGHT    2
#define STATE_BACKWARD 3
#define STATE_STOP     4
#define ADJUST_LEFT    5
#define ADJUST_RIGHT   6
#define BASE_SPEAD     100
#define TURN_ADJUST    -20
#define BACK_ADJUST    20
#define TURN_SLIGHTLY  10

class Motors {
public:
  Motors();

  void setup();

  void forward();
  void forward_adjusting();
  void backward();
  void left();
  void right();
  void stop();
  void adjust_left();
  void adjust_right();
  
  void right90();
  void left90();

  byte getState() { return state; }

private:
  int pinI1;//define I1 interface
  int pinI2;//define I2 interface 
  int speedpinA;//enable motor A
  int pinI3;//define I3 interface 
  int pinI4;//define I4 interface 
  int speedpinB;//enable motor B
  int spead;//define the spead of motor

  int speadA;
  int speadB;
  

  byte state;
};

Motors::Motors() {
  
}

void Motors::setup() {
  pinI1 = 8;
  pinI2 = 11;
  speedpinA = 9;
  pinI3 = 12; 
  pinI4 = 13;
  speedpinB = 10;
  //spead = 127;
  speadA = BASE_SPEAD;
  speadB = speadA + 7;

  state = STATE_STOP;

  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpinB,OUTPUT);
}

void Motors::right() {
   if (state != STATE_RIGHT) {
      stop();
      delay(100);
      state = STATE_RIGHT;
   }
   analogWrite(speedpinA,speadA - TURN_ADJUST);//input a simulation value to set the speed
   analogWrite(speedpinB,speadB - TURN_ADJUST);
   digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
   digitalWrite(pinI3,LOW);
   digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
   digitalWrite(pinI1,HIGH);
}

void Motors::left() {
   if (state != STATE_LEFT) {
     stop();
     delay(100);
     state = STATE_LEFT;
   }
   analogWrite(speedpinA,speadA - TURN_ADJUST);//input a simulation value to set the speed
   analogWrite(speedpinB,speadB - TURN_ADJUST);
   digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
   digitalWrite(pinI3,HIGH);
   digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
   digitalWrite(pinI1,LOW);
}

void Motors::backward() {
  if (state != STATE_BACKWARD) {
     stop();
     delay(100);
     state = STATE_BACKWARD;
  }
  analogWrite(speedpinA,speadA - BACK_ADJUST);//input a simulation value to set the speed
  analogWrite(speedpinB,speadB - BACK_ADJUST);
  digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
  digitalWrite(pinI3,LOW);
  digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
  digitalWrite(pinI1,LOW);
}

void Motors::forward() {
  if (state != STATE_FORWARD) {
    stop();
    delay(100);
    state = STATE_FORWARD;
  }
  analogWrite(speedpinA,speadA);//input a simulation value to set the speed
  analogWrite(speedpinB,speadB);
  digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
  digitalWrite(pinI3,HIGH);
  digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
  digitalWrite(pinI1,HIGH);
}

void Motors::forward_adjusting() {
  //Check if the side measurements are close to each other if they are move forward and stop correction
  float ratio = lasers.getLeft() / (float)lasers.getRight();
  Serial.print("Side Laser Ratio: ");
  Serial.println(ratio,3);
  //if ratio is within 10% we are all good
  //if ratio is 0.5: Right is far away from the wall correct right
  //if ratio is 1.5: Left is far away from wall correct left
  const float variance = 0.15;
  const float lowerlimit = 1 - variance;
  const float upperlimit = 1 + variance;
  
  if (ratio >= lowerlimit && ratio <= upperlimit)
  {
    forward();
  }
  else if (ratio > upperlimit && (lasers.getLeft() != OUT_OF_RANGE && lasers.getRight() != OUT_OF_RANGE))
  {
    adjust_left();
  }
  else if (ratio < lowerlimit && (lasers.getLeft() != OUT_OF_RANGE && lasers.getRight() != OUT_OF_RANGE))
  {
    adjust_right();
  }
}

void Motors::stop() {
  state = STATE_STOP;
  digitalWrite(speedpinA,LOW);// Unenble the pin, to stop the motor. this should be done to avid damaging the motor. 
  digitalWrite(speedpinB,LOW);
  delay(100);
}

void Motors::adjust_left()
{
   if (state != ADJUST_LEFT) {
      stop();
      delay(100);
      state = ADJUST_LEFT;
   }
   analogWrite(speedpinA,speadA - TURN_SLIGHTLY);//input a simulation value to set the speed
   analogWrite(speedpinB,speadB);
   digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
   digitalWrite(pinI3,HIGH);
   digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
   digitalWrite(pinI1,HIGH);
}

void Motors::adjust_right()
{
   if (state != ADJUST_RIGHT) {
      stop();
      delay(100);
      state = ADJUST_RIGHT;
   }
   analogWrite(speedpinA,speadA);//input a simulation value to set the speed
   analogWrite(speedpinB,speadB - TURN_SLIGHTLY);
   digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
   digitalWrite(pinI3,HIGH);
   digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
   digitalWrite(pinI1,HIGH);
}

void Motors::right90() {
  right();
  delay(2000);
}

void Motors::left90() {
  left();
  delay(2000);
}

#endif
