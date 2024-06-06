#include "body_to_head.hpp"
#include "head_tilt.hpp"
#include "servoboard.hpp"
#include "switch.hpp"

// Eyebrow Right
#define EYEBROW_RIGHT_MIN 300
#define EYEBROW_RIGHT_MAX 350
#define EYEBROW_RIGHT 9  // 10th port on servo board, labled 7 in sharpie
void eyebrow_right_set(int input) {
  if (!switch_enabled()) return;

  input = map(input, -127, 127, EYEBROW_RIGHT_MIN, EYEBROW_RIGHT_MAX);  // Translate -127-127 to min-max
  // BtH_data.eyebrow_right_ = input;                                      // Output for body-head communication
  pwm.setPWM(EYEBROW_RIGHT, 0, input);
}

// Eyebrow Left
#define EYEBROW_LEFT_MIN 190
#define EYEBROW_LEFT_MAX 125
#define EYEBROW_LEFT 8  // 9th port on servo board
void eyebrow_left_set(int input) {
  if (!switch_enabled()) return;

  input = map(input, -127, 127, EYEBROW_LEFT_MIN, EYEBROW_LEFT_MAX);  // Translate -127-127 to min-max
  // BtH_data.eyebrow_left_ = input;                                     // Output for body-head communication
  pwm.setPWM(EYEBROW_LEFT, 0, input);
}

void eyebrows_runtime() {
  eyebrow_left_set(HEAD_TILT_CURRENT);
  eyebrow_right_set(-HEAD_TILT_CURRENT);
}