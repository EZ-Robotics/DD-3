#include <Arduino.h>
#include <Servo.h>

#include "joysticks.hpp"
#include "switch.hpp"

#define HEAD_SPIN 5  // Head spin port
Servo headspin;

// The VEX Motor Controller 29's do not output linearly.
// This solves this and makes the inputs linear
// https://www.vexforum.com/t/24cs-motor-control-value-remapping/23959
const unsigned int trueSpeed[128] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
        25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
        28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
        33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
        37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
        41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
        46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
        52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
        61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
        71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
        80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
        88, 89, 89, 90, 90, 127, 127, 127};

// Returns the sign of input
int sgn(int x) {
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}

// Initialize head spin with servo library, based on
// https://forum.arduino.cc/t/arduino-with-vex-motor/187302
void head_spin_init() {
  headspin.attach(HEAD_SPIN);
}

// Sets the head to spin if the switch isn't enabled
void head_spin_set(int input) {
  if (!switch_enabled()) {
    headspin.write(0);
    return;
  }
  input = sgn(input) * trueSpeed[abs(input)];

  headspin.write(map(input, -127, 127, 20, 170));
}

// Make the head spin based on user inputs
void head_spin_runtime() {
  head_spin_set(joystick_channel(CH1));
}