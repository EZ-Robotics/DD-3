#include <Vector.h>

#include "joysticks.hpp"
#include "sbus.h"

// Sbus rx on uart
bfs::SbusRx sbus_rx(&Serial1);

// Input data from sbus
bfs::SbusData data;

// Incase joysticks don't perfectly return to 0, remove the first few values of joystick
#define THRESHOLD 2
int joystick_threshold(int input) {
  return abs(input) > THRESHOLD ? input : 0;
}

const int ELEMENT_COUNT_MAX = 5;
typedef Vector<int> Elements;
int storage_array_x[ELEMENT_COUNT_MAX];
int storage_array_y[ELEMENT_COUNT_MAX];
Elements gyro_x_vector;
Elements gyro_y_vector;
int gyro_x_output = 0;
int gyro_y_output = 0;

// Initialize receiver
void joystick_init() {
  Serial1.begin(9600);
  sbus_rx.Begin();  // Init uart
  for (int i = 0; i < 16; i++) {
    data.ch[i] = 0;
  }
  gyro_x_vector.setStorage(storage_array_x);
  gyro_y_vector.setStorage(storage_array_y);
}

// "Raw" joystick value, for use in this file only
int joystick_channel_raw(int channel) {
  int output = map(data.ch[channel], 172, 1811, -127, 127);
  if (output < -127 || output > 127)
    output = 0;
  return output;
}

void joystick_runtime() {
  if (sbus_rx.Read()) {
    /* Grab the received data */
    data = sbus_rx.data();
  }

  // SMA filter for the gyros in the controller
  if (gyro_x_vector.size() >= gyro_x_vector.max_size())
    gyro_x_vector.remove(0);

  if (gyro_y_vector.size() >= gyro_y_vector.max_size())
    gyro_y_vector.remove(0);

  gyro_x_vector.push_back(joystick_channel_raw(GYRO_X));
  gyro_y_vector.push_back(joystick_channel_raw(GYRO_Y));

  // int xx = 0, yy = 0;
  int max = gyro_x_vector.size();
  for (int i = 0; i < max; i++) {
    gyro_x_output += gyro_x_vector[i];
    gyro_y_output += gyro_y_vector[i];
  }
  gyro_x_output /= max;
  gyro_y_output /= max;
}

// Josystick threshold, clipping output with threshold, based on red curve here https://www.desmos.com/calculator/rcfjjg83zx
double joystick_curve(double x, double t) {
  return (powf(2.718, -(t / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(t / 10)))) * x;
}

// Forward curve, clipping output with threshold, based on red curve here https://www.desmos.com/calculator/rcfjjg83zx
double joystick_curve_fwd(double x, double t) {
  return joystick_threshold(joystick_curve(x, t));
}

// Turn curve, clipping output with threshold, based on red curve here https://www.desmos.com/calculator/rcfjjg83zx
double joystick_curve_turn(double x, double t) {
  return joystick_threshold(joystick_curve(x, t));
}

// Turn -127, 0, 127 into 0, 1, 2 for switches
_switch joystick_tri_switch_raw(int channel) {
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

// Turn -127, 127 into 0, 1 for switches
_switch joystick_dual_switch_raw(int channel) {
  int check = joystick_threshold(joystick_channel_raw(channel));
  int thresh = 127 - THRESHOLD;
  if (check <= -thresh)
    return DOWN;
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

    // Dual Switches
    case CH9 ... CH10:
      output = joystick_dual_switch_raw(channel);
      break;

    // Gyro X
    case GYRO_X:
      output = gyro_x_output;
      break;

    // Gyro Y
    case GYRO_Y:
      output = gyro_y_output;
      break;

    default:
      break;
  }

  return output;
}