#pragma once 

#include <Adafruit_PWMServoDriver.h>

extern Adafruit_PWMServoDriver pwm;
extern bool is_sleep;
void servoboard_init();
void servoboard_sleep(bool input);