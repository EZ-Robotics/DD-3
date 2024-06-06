#include <Adafruit_PWMServoDriver.h>

#include "joysticks.hpp"
#include "servoboard.hpp"
#include "switch.hpp"

#define HEAD_TILT 6  // 10th channel on PCA9685
#define SERVOMIN 350  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 425  // This is the 'maximum' pulse length count (out of 4096)

int HEAD_TILT_CURRENT;

void head_tilt_set(int input) {
  HEAD_TILT_CURRENT = input;
  if (!switch_enabled()) return;

  input = map(input, -127, 127, SERVOMIN, SERVOMAX);
  pwm.setPWM(HEAD_TILT, 0, input);
}

void head_tilt_runtime() {
  head_tilt_set(joystick_channel(CH2));
}