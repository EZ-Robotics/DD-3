#include <Wire.h>

#include "joysticks.hpp"
#include "switch.hpp"

#define SWITCH 13         // Pin 13
#define SWITCH_TIME 1000  // Time to wait after enabling switch before it enables

// Output of the switch
bool switch_output = false;
bool controller_switch_output = false;

// Initialize pin to input
void switch_init() {
  pinMode(SWITCH, INPUT);
}

// Raw switch
bool switch_raw() {
  return digitalRead(SWITCH);
}

// Is the switch enabled?
bool switch_enabled() {
  return switch_output;
}

bool controller_switch_raw() {
  if (joystick_channel(LEFT_DUAL_SWTICH) == DOWN)
    return true;
  return false;
}

bool controller_switch_enabled() {
  return controller_switch_output;
}

int controller_switch_timer = 0;
int starter_timer = 0;
bool last_switch_state = false;
void switch_runtime() {
  // Don't let this function run for the first 3 seconds of program running
  starter_timer += 20;
  if (starter_timer <= 3000) {
    if (controller_switch_raw()) last_switch_state = true;
    return;
  }
  starter_timer = 3000;

  // If the switch starts on, don't let anything run until switch is disabled
  if (last_switch_state) {
    switch_output = false;
    controller_switch_output = false;

    if (!controller_switch_raw())
      last_switch_state = false;
    return;
  }

  // Allow everything but the drive to run
  switch_output = true;

  ///
  // Disable and enabling drive through controller
  ///

  // When the timer reaches SWITCH_TIME, enable the switch
  if (controller_switch_timer >= SWITCH_TIME) {
    controller_switch_output = true;
    controller_switch_timer = SWITCH_TIME;
  }

  // Start a timer with switch is first switched
  // When it turns off, immediately turn it off
  if (controller_switch_raw()) {
    controller_switch_timer += 20;
  } else {
    controller_switch_output = false;
    controller_switch_timer = 0;
  }
}