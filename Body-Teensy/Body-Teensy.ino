#include <Arduino.h>

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
  // body_to_head_init();
  Serial.begin(9600);

  delay(10);
}
void loop() {
  head_tilt_runtime();
  head_spin_runtime();
  drive_runtime();

  // Serial.sprintf("L %i   R %i\n", joystick_channel(CH1), joystick_channel(CH2));
  // Serial.println(joystick_channel(CH1));
  // Serial.println(joystick_channel(CH2));

  // eye_runtime();
  // eyebrows_runtime();
  // body_to_head_send();

  delay(20);  // This must be longer then Head-Teensy.ino delay!
}