#include <Arduino.h>
#include <Servo.h>

#include "joysticks.hpp"
#include "switch.hpp"

// Motor ports
#define R_MOTOR_CH 21
#define L_MOTOR_CH 20

Servo L_MOTOR;  // create servo object to control the ESC
Servo R_MOTOR;  // create servo object to control the ESC

// Initialize the motors with the servo library
void drive_init() {
  L_MOTOR.attach(L_MOTOR_CH, 1000, 2000);  // (pin, min pulse width, max pulse width in microseconds)
  R_MOTOR.attach(R_MOTOR_CH, 1000, 2000);  // (pin, min pulse width, max pulse width in microseconds)
}

// Set the drive motors if the switch is enabled
// Account for slight speed difference between left and right
void drive_set(double l, double r) {
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

// Run the drive based on user inputs
void drive_runtime() {
  double ch3 = joystick_curve_fwd(joystick_channel(CH3));
  double ch4 = joystick_curve_turn(joystick_channel(CH4));
  int left = ch3 + ch4;
  int right = ch3 - ch4;
  drive_set(left, right);
}