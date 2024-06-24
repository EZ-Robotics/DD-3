#include <Adafruit_PWMServoDriver.h>

#include "joysticks.hpp"
#include "servoboard.hpp"
#include "switch.hpp"

#define SERVOMIN 550
#define SERVOMAX 390

#define CENTER_SERVO 6            // unmarked channel on PCA9685
#define CENTER_SERVOMIN SERVOMIN  // This is the 'minimum' pulse length count (out of 4096)
#define CENTER_SERVOMAX SERVOMAX  // This is the 'maximum' pulse length count (out of 4096)

#define RIGHT_SERVO 5            // 6th port on servo board
#define RIGHT_SERVOMIN SERVOMIN  // This is the 'minimum' pulse length count (out of 4096)
#define RIGHT_SERVOMAX SERVOMAX  // This is the 'maximum' pulse length count (out of 4096)

#define LEFT_SERVO 4            // 5th port on servo board
#define LEFT_SERVOMIN SERVOMIN  // This is the 'minimum' pulse length count (out of 4096)
#define LEFT_SERVOMAX SERVOMAX  // This is the 'maximum' pulse length count (out of 4096)

int HEAD_TILT_CURRENT;
int HEAD_HEIGHT_CURRENT;

void head_tilt_set(int height, int forward, int tilt) {
  if (!switch_enabled()) return;

  float servo_center = height + forward;
  float servo_right = height - (0.666 * tilt) - (0.333 * forward);
  float servo_left = height + (0.666 * tilt) - (0.333 * forward);

  double largest_servo = fmax(fabs(servo_left), fabs(servo_right));
  largest_servo = fmax(largest_servo, fabs(servo_center));
  if (largest_servo > 127.0) {
    float scale = 127.0 / largest_servo;
    servo_center = servo_center * scale;
    servo_right = servo_right * scale;
    servo_left = servo_left * scale;
  }

  servo_center = map(servo_center, -127, 127, CENTER_SERVOMIN, CENTER_SERVOMAX);
  pwm.setPWM(CENTER_SERVO, 0, servo_center);

  servo_right = map(servo_right, -127, 127, RIGHT_SERVOMIN, RIGHT_SERVOMAX);
  pwm.setPWM(RIGHT_SERVO, 0, servo_right);

  servo_left = map(servo_left, -127, 127, LEFT_SERVOMIN, LEFT_SERVOMAX);
  pwm.setPWM(LEFT_SERVO, 0, servo_left);
}

void head_tilt_runtime() {
  float height = joystick_channel(RIGHT_SLIDER) - 127.0;
  float forward = joystick_channel(RIGHT_Y);
  float tilt = joystick_channel(RIGHT_X);

  HEAD_TILT_CURRENT = tilt;
  HEAD_HEIGHT_CURRENT = height;

  head_tilt_set((int)height, (int)forward, (int)tilt);
}

/*
Serial.print(switch_enabled());
Serial.print("\t\t\t");
Serial.print("height: ");
Serial.print(height);
Serial.print("\tfwd: ");
Serial.print(forward);
Serial.print("\ttilt: ");
Serial.print(tilt);
Serial.print("\t\tcenter: ");
Serial.print(servo_center);
Serial.print("\tright: ");
Serial.print(servo_right);
Serial.print("\tleft: ");
Serial.print(servo_left);
Serial.print("\n");
*/