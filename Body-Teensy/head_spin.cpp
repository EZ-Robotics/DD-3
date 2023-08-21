#include <Servo.h>

#include "switch.hpp"

#define HEAD_SPIN 3
Servo headspin;

void head_spin_init() {
  headspin.attach(HEAD_SPIN);
}

void head_spin_set(int input) {
  if (!switch_enabled()) return;

  headspin.write(0);
}
