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

void loop() {
  switch_runtime();
  joystick_runtime();
  head_spin_runtime();
  drive_runtime();

  if (joystick_channel(RIGHT_DUAL_SWTICH) == UP) {
    // Eye will randomly look somewhere
    if (eye_counter >= 2000) {
      eye_x_set(random(-70, 70));
      eye_y_set(random(-70, 70));
      eye_counter = 0;
    }

  // Head will randomly tilt
    if (head_tilt_counter >= 5000) {
      head_tilt_set(random(-100, 100));
      head_tilt_counter = 0;
    }

    eye_counter += 20;
    head_tilt_counter += 20;

    // Eyebrows will slowly go in and out
    if (eyebrow_breath <= -127) {
      flipped = true;
    }
    if (eyebrow_breath >= 127) {
      flipped = false;
    }

    if (!flipped) {
      eyebrow_breath -= add_value;
    } else {
      eyebrow_breath += add_value;
    }
    eyebrow_left_set(eyebrow_breath);
    eyebrow_right_set(eyebrow_breath);
  } else {
    eye_runtime();
    eyebrows_runtime();
    head_tilt_runtime();
    eye_counter = 0;
    head_tilt_counter = 0;
  }

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