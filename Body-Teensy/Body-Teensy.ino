#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>
#include <Wire.h>

#include "body_to_head.hpp"
#include "drive.hpp"
#include "eye.hpp"
#include "eyebrows.hpp"
#include "joysticks.hpp"
#include "switch.hpp"

#define HEAD_SPIN 3
Servo headspin;

#define HEAD_TILT 15   // 16th channel on PCA9685
#define SERVOMIN 350   // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 425   // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates

#include <Audio.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

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

void pwm_init() {
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}
void set_tilt(int input) {
  if (switch_enabled()) {
    input = map(input, -127, 127, SERVOMIN, SERVOMAX);
    pwm.setPWM(HEAD_TILT, 0, input);
  }
}

void setup() {
  // put your setup code here, to run once:
  switch_init();
  head_init();
  pwm_init();
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
  set_tilt(joystick_channel(CH2));
  drive_set(left, right);

  /*eye_y_set(127);
  eye_x_set(127);
  eyebrow_right_set(127);
  eyebrow_left_set(127);*/
  body_to_head_send();

  delay(20);  // This must be longer then Head-Teensy.ino delay!
}