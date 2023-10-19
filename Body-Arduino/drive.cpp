#include <Arduino.h>
#include <Servo.h>

#include "joysticks.hpp"
#include "switch.hpp"

// Motor ports
#define R_MOTOR_CH A6
#define L_MOTOR_CH A7

Servo L_MOTOR;  // create servo object to control the ESC
Servo R_MOTOR;  // create servo object to control the ESC

// Initialize the motors with the servo library
void drive_init() {
  L_MOTOR.attach(L_MOTOR_CH, 1000, 2000);  // (pin, min pulse width, max pulse width in microseconds)
  R_MOTOR.attach(R_MOTOR_CH, 1000, 2000);  // (pin, min pulse width, max pulse width in microseconds)
}

// Set the drive motors if the switch is enabled
// Account for slight speed difference between left and right
void drive_set_raw(double l, double r) {
  // If switch is disabled...
  if (!switch_enabled()) {
    l = 0;
    r = 0;
    l = l - 5;
    L_MOTOR.write(map(l, -127, 127, 0, 180));  // Send the signal to the ESC
    R_MOTOR.write(map(r, -127, 127, 0, 180));  // Send the signal to the ESC
    return;
  }

  // If switch is enabled...
  l = l - 5;
  r = r * 1.2;
  L_MOTOR.write(map(l, -127, 127, 0, 180));  // Send the signal to the ESC
  R_MOTOR.write(map(r, -127, 127, 0, 180));  // Send the signal to the ESC
}

// Slew the drive motors to avoid changes in motion that are too large
double l_target = 0.0, r_target = 0.0;
double l_current = 0.0, r_current = 0.0;
const double MAX = 2;
void drive_set(double l, double r) {
  if (!switch_enabled()) {
    l_target = r_target = r_current = l_current = 0.0;
    drive_set_raw(l_target, r_target);
    return;
  }
  l_target = l;
  r_target = r;
  double max = fmax(fabs(l_target), fabs(r_target));
  double min = fmin(fabs(l_target), fabs(r_target));
  double l_add = MAX, r_add = MAX;
  if (fabs(l_target) > fabs(r_target)) {
    l_add = MAX;
    r_add = min / max;
  } else if (fabs(l_target) < fabs(r_target)) {
    l_add = min / max;
    r_add = MAX;
  }

  if (l_current > l_target)
    l_current -= l_add;
  else if (l_current < l_target)
    l_current += l_add;

  if (r_current > r_target)
    r_current -= r_add;
  else if (r_current < r_target)
    r_current += r_add;

  drive_set_raw(l_current, r_current);
}

// Run the drive based on user inputs
void drive_runtime() {
  int speed_selector = joystick_channel(LEFT_TRI_SWTICH);
  double max_speed = 127.0;
  double curve_fwd = 1.0;
  double curve_turn = 1.0;

  // Slowest Speed
  if (speed_selector == 0) {
    max_speed = 55;
    curve_fwd = 1.0;
    curve_turn = 1.0;
  }

  // Middle Speed
  else if (speed_selector == 1) {
    max_speed = 80.0;
    curve_fwd = 1.0;
    curve_turn = 1.0;
  }

  // Fastest Speed
  else {
    max_speed = 127.0;
    curve_fwd = 5.0;
    curve_turn = 8.0;
  }

  double scale = max_speed / 127.0;
  double forward = joystick_curve_fwd(joystick_channel(CH3), curve_fwd) * scale;
  double curve = joystick_curve_turn(joystick_channel(CH4), curve_turn) * scale;

  /*
  double left_speed = forward + std::abs(forward) * curvature;
  double right_speed = forward - std::abs(forward) * curvature;
  double fastest_side = std::max(left_speed, right_speed);

  // normalizes output
  double max = fmax(fabs(left_speed), fabs(right_speed));
  double min = fmin(fabs(left_speed), fabs(right_speed));
  if (max > scale * 127.0) {
    if (fabs(left_speed) > fabs(r_target)) {
      left_speed = MAX;
      right_speed = min / max;
    } else if (fabs(left_speed) < fabs(right_speed)) {
      left_speed = min / max;
      right_speed = MAX;
    }
  }
  */

  double ch3 = joystick_curve_fwd(joystick_channel(CH3), curve_fwd) * scale;
  double ch4 = joystick_curve_turn(joystick_channel(CH4), curve_turn) * scale;
  int left = ch3 + ch4;
  int right = ch3 - ch4;
  drive_set(left, right);
}