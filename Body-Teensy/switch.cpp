#include <Wire.h>

#include "switch.hpp"

#define SWITCH 4

bool switch_enabled() {
  return digitalRead(SWITCH);
}
void switch_init() {
  pinMode(SWITCH, INPUT);
}