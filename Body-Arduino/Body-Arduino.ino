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
  joystick_runtime();
  head_tilt_runtime();
  head_spin_runtime();
  // drive_runtime();

  for (int i = 0; i < 8; i++) {
    Serial.print(joystick_channel(i));
    Serial.print("\t");
  }
  Serial.print("\n");
  // Serial.println(switch_enabled());
  /*
  for (int i = -127; i < 127; i++) {
    head_tilt_set(i);
    drive_set(i, i);
    head_spin_set(i);
    delay(5);
  }

  for (int i = 127; i > -127; i--) {
    head_tilt_set(i);
    drive_set(i, i);
    head_spin_set(i);
    delay(5);
  }
  */

  // eye_runtime();
  // eyebrows_runtime();
  // body_to_head_send();

  delay(20);  // This must be longer then Head-Teensy.ino delay!
}