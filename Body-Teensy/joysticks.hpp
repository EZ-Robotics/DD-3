#pragma once

// Ports for receiver -> teensy
#define CH1 15
#define CH2 14
#define CH3 23
#define CH4 22

void joystick_init();

double joystick_curve_fwd(double x);
double joystick_curve_turn(double x);
int joystick_channel(int channel);