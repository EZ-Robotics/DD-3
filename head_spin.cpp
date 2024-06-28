#include <Arduino.h>
#include <Servo.h>

#include "joysticks.hpp"
#include "switch.hpp"

#define HEAD_POT A0   // Head Potentiometer
#define HEAD_SPIN 12  // Head spin port
Servo headspin;

// Returns the sign of input
double sgn(double x) {
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}

double prev_current = 0, pid_target = 0, integral = 0, prev_error = 0, output = 0, derivative = 0, SPIN_VELOCITY = 0, HEAD_POSITION = 0;
bool reset_i_sgn = true;
double kp = 1;
double ki = 0;
double kd = 1;
double start_i = 0;
double iterate_pid(double current) {
  double error = pid_target - current;

  // calculate derivative on measurement instead of error to avoid "derivative kick"
  // https://www.isa.org/intech-home/2023/june-2023/features/fundamentals-pid-control
  derivative = current - prev_current;

  if (ki != 0) {
    // Only compute i when within a threshold of target
    if (fabs(error) < start_i)
      integral += error;

    // Reset i when the sign of error flips
    if (sgn(error) != sgn(prev_current) && reset_i_sgn)
      integral = 0;
  }

  output = (error * kp) + (integral * ki) - (derivative * kd);

  prev_current = current;
  prev_error = error;

  return output;
}

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

// Initialize head spin with servo library, based on
// https://forum.arduino.cc/t/arduino-with-vex-motor/187302
void head_spin_init() {
  headspin.attach(HEAD_SPIN);
}

// max left 200
// 560 center
// 920

#define HEAD_LEFT 200
#define HEAD_RIGHT 920
void set_pid_target(double target) {
  pid_target = map(target, -127, 127, HEAD_LEFT, HEAD_RIGHT);
}

// Sets the head to spin if the switch isn't enabled
void head_spin_set(int input) {
  if (!switch_enabled()) {
    headspin.write(0);
    return;
  }
  if (input > 127) {
    input = 127;
  } else if (input < -127) {
    input = -127;
  }

  input = sgn(input) * trueSpeed[abs(input)];
  input *= -1;

  headspin.write(map(input, -127, 127, 20, 170));
}

double get_pot() {
  return analogRead(HEAD_POT);
}

// Make the head spin based on user inputs
void head_spin_runtime() {
  // head_spin_set(joystick_channel(LEFT_SLIDER) - 127);
  set_pid_target(joystick_channel(RIGHT_SLIDER) - 127.0);

  // SPIN_VELOCITY = derivative;
  SPIN_VELOCITY = pid_target - get_pot();
  HEAD_POSITION = map(get_pot(), HEAD_LEFT - 50, HEAD_RIGHT + 50, -127, 127);

  head_spin_set(iterate_pid(get_pot()));
}