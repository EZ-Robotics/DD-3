#include <Wire.h>

#include "joysticks.hpp"

// Scalers for joystick curve
#define FWD_SCALE 5.0
#define TURN_SCALE 8.0

// Incase joysticks don't perfectly return to 0, remove the first few values of joystick
#define THRESHOLD 2
int joystick_threshold(int input) {
  return abs(input) > THRESHOLD ? input : 0;
}

// Initialize receiver
void joystick_init() {
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
}

// "Raw" joystick value, for use in this file only
int joystick_channel_raw(int channel) {
  return map(pulseIn(channel, HIGH, 30000), 990, 2014, -127, 127);
}

// Forward curve, clipping output with threshold, based on red curve here https://www.desmos.com/calculator/rcfjjg83zx
double joystick_curve_fwd(double x) {
  double curve = (powf(2.718, -(FWD_SCALE / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(FWD_SCALE / 10)))) * x;
  return joystick_threshold(curve);
}

// Turn curve, clipping output with threshold, based on red curve here https://www.desmos.com/calculator/rcfjjg83zx
double joystick_curve_turn(double x) {
  double curve = (powf(2.718, -(TURN_SCALE / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(TURN_SCALE / 10)))) * x;
  return joystick_threshold(curve);
}

// Normal output, clipping output with threshold
int joystick_channel(int channel) {
  return joystick_threshold(joystick_channel_raw(channel));
}