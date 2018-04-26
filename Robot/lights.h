/*
 * Control the onboard lights for the car.
 */

#ifndef __LIGHTS_H__
#define __LIGHTS_H__

#define LEFT_PIN   2
#define FRONT_PIN  6
#define RIGHT_PIN  7

#define LIGHT_LEFT  0
#define LIGHT_FRONT 1
#define LIGHT_RIGHT 2

class Lights {
public:
  Lights();

  // Turn light on
  void on(int light);
  // Turn light off
  void off(int light);

  // Set the light state
  void set(int light, int high_low);

  // Get state of light
  int get(int light);
  
private:
  int state[3];
  int pin[3];
};


Lights::Lights() {
  pin[LIGHT_LEFT] = LEFT_PIN;
  pin[LIGHT_FRONT] = FRONT_PIN;
  pin[LIGHT_RIGHT] = RIGHT_PIN;

  for (int i = 0; i < 3; i++) {
    state[i] = LOW;
    pinMode(pin[i], OUTPUT);
    digitalWrite(pin[i], LOW);
  }
}

void Lights::on(int light) {
  state[light] = HIGH;
  digitalWrite(pin[light], HIGH);
}

void Lights::off(int light) {
  state[light] = LOW;
  digitalWrite(pin[light], LOW);
}

void Lights::set(int light, int high_low) {
  state[light] = high_low;
  digitalWrite(pin[light], high_low);
}

int Lights::get(int light) {
  return state[light];
}

#endif
