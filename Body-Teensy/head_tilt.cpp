#include <Adafruit_PWMServoDriver.h>

#include "joysticks.hpp"
#include "switch.hpp"

#define HEAD_TILT 15   // 16th channel on PCA9685
#define SERVOMIN 350   // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 425   // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

int HEAD_TILT_CURRENT;

void head_tilt_init() {
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

void head_tilt_set(int input) {
  HEAD_TILT_CURRENT = input;
  if (!switch_enabled()) return;

  input = map(input, -127, 127, SERVOMIN, SERVOMAX);
  pwm.setPWM(HEAD_TILT, 0, input);
}

void head_tilt_runtime() {
  head_tilt_set(joystick_channel(CH2));
}