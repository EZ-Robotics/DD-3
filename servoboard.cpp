#include <Adafruit_PWMServoDriver.h>

#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void servoboard_init() {
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

bool is_sleep = false;
void servoboard_sleep(bool input) {
  is_sleep = input;
  if (input) {
    pwm.sleep();
  } else {
    pwm.wakeup();
  }
}