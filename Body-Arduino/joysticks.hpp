#pragma once

// Ports for receiver -> arduino
#define CH1 0   // Right Y
#define CH2 1   // Right X
#define CH3 2   // Left Y
#define CH4 3   // Left X
#define CH5 4   // Right Slider
#define CH6 5   // Left Slider
#define CH7 6   // Right 3 Switch
#define CH8 7   // Left 3 Switch
#define CH9 8   // Right 2 Switch
#define CH10 9  // Left 2 Switch
#define CH11 10
#define CH12 11
#define CH13 12
#define CH14 13
#define CH15 14
#define CH16 15

#define RIGHT_Y CH1
#define RIGHT_X CH2
#define LEFT_Y CH3
#define LEFT_X CH4
#define RIGHT_SLIDER CH5
#define LEFT_SLIDER CH6
#define RIGHT_TRI_SWITCH CH7
#define LEFT_TRI_SWTICH CH8
#define RIGHT_DUAL_SWTICH CH9
#define LEFT_DUAL_SWTICH CH10

enum _switch { DOWN = 2,
               MIDDLE = 1,
               UP = 0
};

void joystick_init();

void joystick_runtime();

double joystick_curve_fwd(double x, double t);
double joystick_curve_turn(double x, double t);
int joystick_channel(int channel);