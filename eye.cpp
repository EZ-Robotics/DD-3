#include "body_to_head.hpp"
#include "joysticks.hpp"
#include "servoboard.hpp"
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
#define EYE_Y_MIN 375
#define EYE_Y_MID 250
#define EYE_Y_MAX 235
#define EYE_Y 5  // 6th port on servo board
void eye_y_set(int input) {
  if (!switch_enabled()) return;  // Return if switch isn't enabled

  input = translate(input, -127, 127, EYE_Y_MIN, EYE_Y_MID, EYE_Y_MAX);  // Translate -127-127 to min-mid-max
  // BtH_data.eye_y_ = input;                                               // Output for body-head communication
  pwm.setPWM(EYE_Y, 0, input);
}

// Eye X
#define EYE_X_MIN 200
#define EYE_X_MID 250
#define EYE_X_MAX 350
#define EYE_X 4  // 5th port on servo board
void eye_x_set(int input) {
  if (!switch_enabled()) return;  // Return if switch isn't enabled

  input = translate(input, -127, 127, EYE_X_MIN, EYE_X_MID, EYE_X_MAX);  // Translate -127-127 to min-mid-max
  // BtH_data.eye_x_ = input;                                              // Output for body-head communication
  pwm.setPWM(EYE_X, 0, input);
}

void eye_runtime() {
  // Make the eye more sensitive then the head
  int output = (-joystick_channel(CH1)) * 4;
  output = output > 127 ? 127 : (output < -127 ? -127 : output);
  eye_x_set(output);

  float eye_y_center = joystick_channel(RIGHT_SLIDER) - 127.0;
  eye_y_set(eye_y_center);
}