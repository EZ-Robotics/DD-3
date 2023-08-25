#include <Wire.h>

#include "switch.hpp"

#define SWITCH 3

bool switch_enabled() {
  return digitalRead(SWITCH);
}
void switch_init() {
  pinMode(SWITCH, INPUT);
}