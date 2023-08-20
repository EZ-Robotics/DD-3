#include "body_to_head.hpp"
#include "switch.hpp"

// Eyebrow Right
#define EYEBROW_RIGHT_MIN 300
#define EYEBROW_RIGHT_MAX 400
void eyebrow_right_set(int input) {
  if (!switch_enabled()) return;

  input = map(input, -127, 127, EYEBROW_RIGHT_MIN, EYEBROW_RIGHT_MAX);
  BtH_data.eyebrow_right_ = input;
}

// Eyebrow Left
#define EYEBROW_LEFT_MIN 200
#define EYEBROW_LEFT_MAX 150
void eyebrow_left_set(int input) {
  if (!switch_enabled()) return;

  input = map(input, -127, 127, EYEBROW_LEFT_MIN, EYEBROW_LEFT_MAX);
  BtH_data.eyebrow_left_ = input;
}
