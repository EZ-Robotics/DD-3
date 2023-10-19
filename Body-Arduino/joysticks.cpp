#include "joysticks.hpp"
#include "sbus.h"  // Library

// Sbus rx on uart
bfs::SbusRx sbus_rx(&Serial1);

// Input data from sbus
bfs::SbusData data;

// Incase joysticks don't perfectly return to 0, remove the first few values of joystick
#define THRESHOLD 2
int joystick_threshold(int input) {
  return abs(input) > THRESHOLD ? input : 0;
}

// Initialize receiver
void joystick_init() {
  Serial1.begin(9600);
  sbus_rx.Begin();  // Init uart
  for (int i = 0; i < 16; i++) {
    data.ch[i] = 0;
  }
}

void joystick_runtime() {
  if (sbus_rx.Read()) {
    /* Grab the received data */
    data = sbus_rx.data();
  }
}

// "Raw" joystick value, for use in this file only
int joystick_channel_raw(int channel) {
  int output = map(data.ch[channel], 172, 1811, -127, 127);
  if (output < -127 || output > 127)
    output = 0;
  return output;
}

// Forward curve, clipping output with threshold, based on red curve here https://www.desmos.com/calculator/rcfjjg83zx
double joystick_curve_fwd(double x, double t) {
  double curve = (powf(2.718, -(t / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(t / 10)))) * x;
  return joystick_threshold(curve);
}

// Turn curve, clipping output with threshold, based on red curve here https://www.desmos.com/calculator/rcfjjg83zx
double joystick_curve_turn(double x, double t) {
  double curve = (powf(2.718, -(t / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(t / 10)))) * x;
  return joystick_threshold(curve);
}

// Turn -127, 0, 127 into 0, 1, 2 for switches
_tri_switch joystick_tri_switch_raw(int channel) {
  int check = joystick_threshold(joystick_channel_raw(channel));
  int thresh = 127 - THRESHOLD;
  if (check <= -thresh)
    return DOWN;
  else if (check == 0)
    return MIDDLE;
  else if (check >= thresh)
    return UP;
  return DOWN;
}

// Normal output, clipping output with threshold
int joystick_channel(int channel) {
  int output = 0;

  switch (channel) {
    // Joysticks
    case CH1 ... CH4:
      output = joystick_threshold(joystick_channel_raw(channel));
      break;

    // Sliders
    case CH5 ... CH6:
      // Remap -127, 127 to 0, 255
      output = map(joystick_channel_raw(channel), -127, 127, 0, 255);
      break;

    // Tri Switches
    case CH7 ... CH8:
      output = joystick_tri_switch_raw(channel);
      break;

    default:
      break;
  }

  return output;
}