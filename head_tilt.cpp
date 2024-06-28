#include <Adafruit_PWMServoDriver.h>

#include "head_spin.hpp"
#include "joysticks.hpp"
#include "servoboard.hpp"
#include "switch.hpp"

#define SERVOMIN 530  // 550
#define SERVOMAX 400  // 390

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
  float height = joystick_channel(LEFT_SLIDER) - 127;
  float og_forward = joystick_channel(RIGHT_Y);
  float og_tilt = joystick_channel(RIGHT_X);

  float ratio = fabs(HEAD_POSITION) / 127.0;
  // forward = (ratio * tilt) + (ratio2 * forward);
  // tilt = (ratio * forward) + (ratio2 * tilt);

  // float forward = ((1 - ratio) * og_forward);
  // float tilt = ((HEAD_POSITION / 127.0) * og_forward);

  float tilt = ((1 - ratio) * og_tilt) + ((HEAD_POSITION / 127.0) * og_forward);
  float forward = ((HEAD_POSITION / -127.0) * og_tilt) + ((1 - ratio) * og_forward);

  Serial.print("pre: ");
  Serial.print(og_forward);
  Serial.print("\t");
  Serial.print(og_tilt);
  Serial.print("\t\t");
  Serial.print("post: ");
  Serial.print(forward);
  Serial.print("\t");
  Serial.print(tilt);
  Serial.println("");

  HEAD_TILT_CURRENT = tilt;
  HEAD_HEIGHT_CURRENT = height;

  head_tilt_set((int)height, (int)forward, (int)tilt);
}
