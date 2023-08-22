#include "body_to_head.hpp"
#include "head_tilt.hpp"
#include "switch.hpp"

// Eyebrow Right
#define EYEBROW_RIGHT_MIN 275
#define EYEBROW_RIGHT_MAX 400
void eyebrow_right_set(int input) {
  if (!switch_enabled()) return;

  input = map(input, -127, 127, EYEBROW_RIGHT_MIN, EYEBROW_RIGHT_MAX);  // Translate -127-127 to min-max
  BtH_data.eyebrow_right_ = input;                                      // Output for body-head communication
}

// Eyebrow Left
#define EYEBROW_LEFT_MIN 250
#define EYEBROW_LEFT_MAX 150
void eyebrow_left_set(int input) {
  if (!switch_enabled()) return;

  input = map(input, -127, 127, EYEBROW_LEFT_MIN, EYEBROW_LEFT_MAX);  // Translate -127-127 to min-max
  BtH_data.eyebrow_left_ = input;                                     // Output for body-head communication
}

void eyebrows_runtime() {
  eyebrow_left_set(HEAD_TILT_CURRENT);
  eyebrow_right_set(-HEAD_TILT_CURRENT);
}