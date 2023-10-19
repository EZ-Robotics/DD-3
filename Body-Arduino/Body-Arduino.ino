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
  switch_runtime();
  joystick_runtime();
  head_tilt_runtime();
  head_spin_runtime();
  drive_runtime();

  /*
  Serial.print(switch_enabled());
  Serial.print("\t");
  Serial.print(joystick_channel(CH1));
  Serial.print("\t");
  Serial.print(joystick_channel(CH2));
  Serial.print("\t");
  Serial.print(joystick_channel(CH3));
  Serial.print("\t");
  Serial.print(joystick_channel(CH4));
  Serial.print("\n");
  */

  // eye_runtime();
  // eyebrows_runtime();
  // body_to_head_send();

  delay(20);  // This must be longer then Head-Teensy.ino delay!
}