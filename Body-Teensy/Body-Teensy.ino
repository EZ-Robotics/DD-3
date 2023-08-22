#include "body_to_head.hpp"
#include "drive.hpp"
#include "eye.hpp"
#include "eyebrows.hpp"
#include "head_spin.hpp"
#include "head_tilt.hpp"
#include "joysticks.hpp"
#include "switch.hpp"

void setup() {
  switch_init();
  head_spin_init();
  head_tilt_init();
  drive_init();
  joystick_init();
  body_to_head_init();

  delay(10);
}

int test = 127;

void loop() {
  head_tilt_runtime();
  head_spin_runtime();
  // drive_runtime();

  eye_runtime();
  eyebrows_runtime();

  body_to_head_send();

  delay(20);  // This must be longer then Head-Teensy.ino delay!
}