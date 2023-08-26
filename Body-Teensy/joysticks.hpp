#pragma once

// Ports for receiver -> teensy
#define CH1 6
#define CH2 7
#define CH3 8
#define CH4 9

void joystick_init();

double joystick_curve_fwd(double x);
double joystick_curve_turn(double x);
int joystick_channel(int channel);