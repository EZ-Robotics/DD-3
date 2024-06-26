#include <Wire.h>

#include "joysticks.hpp"
#include "switch.hpp"

#define SWITCH 13         // Pin 13
#define SWITCH_TIME 1000  // Time to wait after enabling switch before it enables

// Output of the switch
bool startup_switch_output = false;
bool controller_switch_output = false;

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
  return startup_switch_output;
}

// Raw controller switch
bool controller_switch_raw() {
  if (joystick_channel(LEFT_DUAL_SWTICH) == DOWN)
    return true;
  return false;
}

// Is controller switch enabled?
bool controller_switch_enabled() {
  return controller_switch_output;
}

// One function to check joystick kill switch and body kill switch
bool drive_switch_enabled() {
  if (!controller_switch_enabled())
    return true;
  return false;
}

int right_y_vel = 0, right_x_vel = 0, left_y_vel = 0, left_x_vel = 0;
int last_right_y = 0, last_right_x = 0, last_left_y = 0, last_left_x = 0;
int joy_vel_timer = 0;

bool are_joysticks_running() {
  if (right_y_vel == 0 && right_x_vel == 0 && left_y_vel == 0 && left_x_vel == 0) {
    if (joy_vel_timer >= 1000)
      return false;

    joy_vel_timer += 20;
  } else {
    joy_vel_timer = 0;
  }

  return true;
}

int xx = 0, yy = 0;

int controller_switch_timer = 0;
int starter_timer = 0;
bool last_switch_state = false;
int last_x = 0, last_y = 0;
int afk_timer = 0;
void switch_runtime() {
  right_y_vel = joystick_channel(RIGHT_Y) - last_right_y;
  right_x_vel = joystick_channel(RIGHT_X) - last_right_x;
  left_y_vel = joystick_channel(LEFT_Y) - last_left_y;
  left_x_vel = joystick_channel(LEFT_X) - last_left_x;

  last_right_y = joystick_channel(RIGHT_Y);
  last_right_x = joystick_channel(RIGHT_X);
  last_left_y = joystick_channel(LEFT_Y);
  last_left_x = joystick_channel(LEFT_X);

  // Don't let this function run for the first 3 seconds of program running
  starter_timer += 20;
  if (starter_timer <= 3000) {
    if (controller_switch_raw()) last_switch_state = true;
    return;
  }
  starter_timer = 3000;

  // If the switch starts on, don't let anything run until switch is disabled
  if (last_switch_state) {
    startup_switch_output = false;
    controller_switch_output = false;

    if (!controller_switch_raw())
      last_switch_state = false;
    return;
  }

  // Allow everything but the drive to run
  startup_switch_output = true;

  ///
  // Disable and enabling drive through controller
  ///

  // Disable drive if the controller is set down for a certain amount of time
  if (controller_switch_output & !are_joysticks_running()) {
    // Current values
    int cur_x = joystick_channel(GYRO_X);
    int cur_y = joystick_channel(GYRO_Y);

    // Figure out the velocity of the controller
    int x = cur_x - last_x;
    int y = cur_y - last_y;

    // Give wiggle room for noise
    x = abs(x) <= 1 ? 0 : x;
    y = abs(y) <= 1 ? 0 : y;

    last_x = cur_x;
    last_y = cur_y;

    // If X and Y velocity are 0, and either X or Y isn't currently at 0 degrees, start the timer
    if (x == 0 && y == 0 && (cur_x != 0 || cur_y != 0))
      afk_timer += 20;
    else
      afk_timer = 0;

  } else {
    afk_timer = 0;
  }

  // Once the timer has reached 2000, disable everything on the robot
  if (afk_timer >= 2000) {
    controller_switch_timer = false;
    startup_switch_output = false;
    last_switch_state = true;
    controller_switch_timer = 0;
    afk_timer = 0;
    return;
  }

  // When the timer reaches SWITCH_TIME, enable the switch
  if (controller_switch_timer >= SWITCH_TIME) {
    controller_switch_output = true;
    controller_switch_timer = SWITCH_TIME;
  }

  // Start a timer with switch is first switched
  // When it turns off, immediately turn it off
  if (controller_switch_raw()) {
    controller_switch_timer += 20;
  } else {
    controller_switch_output = false;
    controller_switch_timer = 0;
  }
}