#include "body_to_head.hpp"
#include "head_tilt.hpp"
#include "joysticks.hpp"
#include "servoboard.hpp"
#include "switch.hpp"

#define SERVO_MIN 350
#define SERVO_MAX 425

// Eyebrow Right
#define EYEBROW_RIGHT_MIN SERVO_MIN
#define EYEBROW_RIGHT_MAX SERVO_MAX
#define EYEBROW_RIGHT 9  // 10th port on servo board, labled 7 in sharpie
void eyebrow_right_set(int input) {
  if (!switch_enabled()) return;

  input = map(input, -127, 127, EYEBROW_RIGHT_MIN, EYEBROW_RIGHT_MAX);  // Translate -127-127 to min-max
  pwm.setPWM(EYEBROW_RIGHT, 0, input);
}

// Eyebrow Left
#define EYEBROW_LEFT_MIN SERVO_MIN
#define EYEBROW_LEFT_MAX SERVO_MAX
#define EYEBROW_LEFT 11  // 12th port on servo board
void eyebrow_left_set(int input) {
  if (!switch_enabled()) return;

  input = map(input, -127, 127, EYEBROW_LEFT_MIN, EYEBROW_LEFT_MAX);  // Translate -127-127 to min-max
  pwm.setPWM(EYEBROW_LEFT, 0, input);
}

void eyebrows_runtime() {
  /*
  double left = -HEAD_HEIGHT_CURRENT + HEAD_TILT_CURRENT;
  double right = -HEAD_HEIGHT_CURRENT - HEAD_TILT_CURRENT;

  double largest_servo = fmax(fabs(left), fabs(right));
  if (largest_servo > 127.0) {
    float scale = 127.0 / largest_servo;
    left = left * scale;
    right = right * scale;
  }
  */

  float left = HEAD_TILT_CURRENT;
  float right = -HEAD_TILT_CURRENT;

  Serial.print(joystick_channel(RIGHT_SLIDER) - 127);
  Serial.print("\t\t");
  Serial.print(HEAD_TILT_CURRENT);
  Serial.print("\t\t");
  Serial.print(left);
  Serial.print("\t");
  Serial.print(right);
  Serial.print("\n");

  //eyebrow_right_set(joystick_channel(RIGHT_SLIDER) - 127);
   eyebrow_left_set(-left);
   eyebrow_right_set(left);
}