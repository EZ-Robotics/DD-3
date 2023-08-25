#pragma once

// Ports for receiver -> teensy
#define CH1 A1
#define CH2 A0
#define CH3 A3
#define CH4 A2

void joystick_init();

double joystick_curve_fwd(double x);
double joystick_curve_turn(double x);
int joystick_channel(int channel);