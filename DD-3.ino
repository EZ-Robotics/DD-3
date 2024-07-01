#include <Arduino.h>

#include "body_to_head.hpp"
#include "drive.hpp"
#include "eye.hpp"
#include "eyebrows.hpp"
#include "head_spin.hpp"
#include "head_tilt.hpp"
#include "joysticks.hpp"
#include "servoboard.hpp"
#include "switch.hpp"

void setup() {
  switch_init();
  head_spin_init();
  servoboard_init();
  drive_init();
  joystick_init();
  body_to_head_init();
  Serial.begin(9600);

  delay(10);
}

int eye_counter = 0;
int head_tilt_counter = 0;
int eyebrow_breath = 127;
bool flipped = false;
int add_value = 3;

_switch last_pos = DOWN;

void loop() {
  switch_runtime();
  joystick_runtime();
  head_spin_runtime();
  drive_runtime();

  // eyebrows_runtime();
  head_tilt_runtime();

  _switch cur = joystick_channel(RIGHT_DUAL_SWTICH);

  if (cur == UP && last_pos != cur) {
    servoboard_sleep(true);
  } else if (cur == DOWN && last_pos != cur) {
    servoboard_sleep(false);
  }
  last_pos = cur;

  delay(10);
}