#pragma once

// Ports for receiver -> arduino
#define CH1 0  // Right Y
#define CH2 1  // Right X
#define CH3 2  // Left Y
#define CH4 3  // Left X
#define CH5 4  // Right Slider
#define CH6 5  // Left Slider
#define CH7 6  // Right 3 switch
#define CH8 7  // Left 3 switch
#define CH9 8
#define CH10 9
#define CH11 10
#define CH12 11
#define CH13 12
#define CH14 13
#define CH15 14
#define CH16 15

enum _tri_switch { DOWN,
                   MIDDLE,
                   UP
};

void joystick_init();

void joystick_runtime();

double joystick_curve_fwd(double x);
double joystick_curve_turn(double x);
int joystick_channel(int channel);