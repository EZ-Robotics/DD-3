#include "body_to_head.hpp"
#include "joysticks.hpp"
#include "switch.hpp"

// Because the servos have linkages that aren't perfect, the servos aren't 1:1 to eye movement
// This lets me define a centerpoint to solve this problem
double translate(double input, double out_min, double out_max, double in_min, double in_mid, double in_max) {
  double out_mid = (out_min + out_max) / 2.0;

  if (input > out_mid)
    return map(input, out_mid, out_max, in_mid, in_max);
  else if (input < out_mid)
    return map(input, out_min, out_mid, in_min, in_mid);

  return in_mid;
}

// Eye y
#define EYE_Y_MIN 150
#define EYE_Y_MID 225
#define EYE_Y_MAX 275
void eye_y_set(int input) {
  if (!switch_enabled()) return;  // Return if switch isn't enabled

  input = translate(input, -127, 127, EYE_Y_MIN, EYE_Y_MID, EYE_Y_MAX);  // Translate -127-127 to min-mid-max
  BtH_data.eye_y_ = input;                                               // Output for body-head communication
}

// Eye X
#define EYE_X_MIN 200
#define EYE_X_MID 250
#define EYE_X_MAX 350
void eye_x_set(int input) {
  if (!switch_enabled()) return;  // Return if switch isn't enabled

  input = translate(input, -127, 127, EYE_X_MIN, EYE_X_MID, EYE_X_MAX);  // Translate -127-127 to min-mid-max
  BtH_data.eye_x_ = input;                                               // Output for body-head communication
}

void eye_runtime() {
  eye_x_set(-joystick_channel(CH1));
}