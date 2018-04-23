/*
 * Control the motors of the car.
 */

#define STATE_FORWARD  0
#define STATE_LEFT     1
#define STATE_RIGHT    2
#define STATE_BACKWARD 3
#define STATE_STOP     4
#define ADJUST_LEFT    5
#define ADJUST_RIGHT   6
class Motors {
public:
  Motors();

  void setup();

  void forward();
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
  spead = 80;

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
   analogWrite(speedpinA,spead);//input a simulation value to set the speed
   analogWrite(speedpinB,spead);
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
   analogWrite(speedpinA,spead);//input a simulation value to set the speed
   analogWrite(speedpinB,spead);
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
  analogWrite(speedpinA,spead);//input a simulation value to set the speed
  analogWrite(speedpinB,spead);
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
  analogWrite(speedpinA,spead);//input a simulation value to set the speed
  analogWrite(speedpinB,spead);
  digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
  digitalWrite(pinI3,HIGH);
  digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
  digitalWrite(pinI1,HIGH);
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
   analogWrite(speedpinA,spead);//input a simulation value to set the speed
   analogWrite(speedpinB,spead + 4);
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
   analogWrite(speedpinA,spead + 7);//input a simulation value to set the speed
   analogWrite(speedpinB,spead);
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

