#include <Wire.h>

#include "joysticks.hpp"

// Initialize receiver
void joystick_init() {
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
}

// Scalers for joystick curve
#define FWD_SCALE 5.0
#define TURN_SCALE 8.0

double joystick_curve_fwd(double x) {
  return (powf(2.718, -(FWD_SCALE / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(FWD_SCALE / 10)))) * x;
}
double joystick_curve_turn(double x) {
  return (powf(2.718, -(TURN_SCALE / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(TURN_SCALE / 10)))) * x;
}

int joystick_channel(int channel) {
  return map(pulseIn(channel, HIGH, 30000), 990, 2014, -127, 127);
}