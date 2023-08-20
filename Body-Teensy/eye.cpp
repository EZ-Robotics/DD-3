#include "body_to_head.hpp"
#include "switch.hpp"

// Eye y
#define EYE_Y_MIN 150
#define EYE_Y_MAX 300
void eye_y_set(int input) {
  if (!switch_enabled()) return; // Return if switch isn't enabled

  input = map(input, -127, 127, EYE_Y_MIN, EYE_Y_MAX);
  BtH_data.eye_y_ = input;
}

// Eye X
#define EYE_X_MIN 150
#define EYE_X_MAX 300
void eye_x_set(int input) {
  if (!switch_enabled()) return; // Return if switch isn't enabled

  input = map(input, -127, 127, EYE_X_MIN, EYE_X_MAX);
  BtH_data.eye_x_ = input;
}