#include <Wire.h>

#include "switch.hpp"

#define SWITCH 13         // Pin 13
#define SWITCH_TIME 1000  // Time to wait after enabling switch before it enables

// Output of the switch
bool switch_output = false;

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

int switch_timer = 0;
void switch_runtime() {
  // When the timer reaches SWITCH_TIME, enable the switch
  if (switch_timer >= SWITCH_TIME) {
    switch_output = true;
    switch_timer = SWITCH_TIME;
  }

  // Start a timer with switch is first switched
  // When it turns off, immediately turn it off
  if (switch_raw()) {
    switch_timer += 20;
  } else {
    switch_output = false;
    switch_timer = 0;
  }
}