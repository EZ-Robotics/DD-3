#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>
#include <Wire.h>

#include "body_to_head.hpp"
#include "drive.hpp"
#include "eye.hpp"
#include "eyebrows.hpp"
#include "head_tilt.hpp"
#include "joysticks.hpp"
#include "switch.hpp"

#define HEAD_SPIN 3
Servo headspin;

void head_set(int input) {
  if (switch_enabled()) {
    headspin.write(map(input, -127, 127, 20, 170));
  } else {
    headspin.write(0);
  }
}
void head_init() {
  headspin.attach(HEAD_SPIN);
}

void setup() {
  // put your setup code here, to run once:
  switch_init();
  head_init();
  head_tilt_init();
  drive_init();
  joystick_init();
  body_to_head_init();

  delay(10);
}

void loop() {
  double ch3 = joystick_curve_fwd(joystick_channel(CH3));
  double ch4 = joystick_curve_turn(joystick_channel(CH4));
  int left = ch3 + ch4;
  int right = ch3 - ch4;
  head_set(joystick_channel(CH1));
  head_tilt_set(joystick_channel(CH2));
  drive_set(left, right);

  /*eye_y_set(127);
  eye_x_set(127);
  eyebrow_right_set(127);
  eyebrow_left_set(127);*/
  body_to_head_send();

  delay(20);  // This must be longer then Head-Teensy.ino delay!
}