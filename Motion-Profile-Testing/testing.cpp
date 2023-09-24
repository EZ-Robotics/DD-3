#include <cmath>
#include <iostream>
using namespace std;

// Constants
const double MAX_VELOCITY = 5.0;
const double MAX_ACCELERATION = 0.5;
const double MAX_DECELERATION = 1.0;

// Return sig of input
int sgn(int input) {
  if (input > 0)
    return 1;
  else if (input < 0)
    return -1;
  return 0;
}

int current_position = 0;

void profile(int target) {
  int sign = sgn(target - current_position);  // Am I going fwd or rev?

  // Fwd vs rev constants
  double max_accel = MAX_ACCELERATION * sign;
  double max_decel = MAX_DECELERATION * sign;
  double max_vel = MAX_VELOCITY * sign;
  double increment = max_accel;  // How much to add each iteration

  double error = target - current_position;

  double steps_to_accel = (MAX_VELOCITY / MAX_ACCELERATION);
  double steps_to_decel = (MAX_VELOCITY / MAX_DECELERATION);

  double dist_to_accel = (steps_to_accel * MAX_VELOCITY) / 2.0;
  double dist_to_decel = (steps_to_decel * MAX_VELOCITY) / 2.0;
  double steps_to_cruise = (fabs(error) - (dist_to_accel + dist_to_decel)) / MAX_VELOCITY;
  double total_steps = steps_to_accel + steps_to_decel + steps_to_cruise;
  // double steps_to_decel =
  // Calculate total steps, it starts decelerating at total steps - 1 velocity step

  std::cout << "Current: " << current_position << "\n";
  std::cout << "Target: " << target << "\n\n";
  std::cout << "Accel Rate: " << max_accel << "\n";
  std::cout << "Decel Rate: " << max_decel << "\n";
  std::cout << "Vel Rate: " << max_vel << "\n\n";
  std::cout << "Steps to Accel: " << steps_to_accel << "\n";
  std::cout << "Steps to Decel: " << steps_to_decel << "\n";
  std::cout << "Steps to Cruise: " << steps_to_cruise << "\n";
  std::cout << "Total Steps: " << total_steps << "\n\n";

  int step = 1;
  std::cout << "0\t0\n";

  // Run this while current position is smaller than target
  // while (sgn(error) == sign) {
  while (step <= total_steps) {
    // std::cout << increment << "\n";
    // std::cout << current_position << "\n";
    std::cout << step << "\t" << increment << "\n";

    // Increase current position
    current_position += increment;

    // Change acceleration rates
    if (step >= steps_to_accel + steps_to_cruise) {
      increment -= max_decel;                              // Decrease velocity over time (negative acceleration!)
      increment = sgn(increment) != sign ? 0 : increment;  // Make sure this can never go below 0
    } else if (step >= steps_to_accel) {
      increment = max_vel;  // Keep velocity constant, we're at max now
    } else {
      increment += max_accel;                                             // Increase velocity over time (acceleration!)
      increment = fabs(increment) > fabs(max_vel) ? max_vel : increment;  // Make sure this can never surpass max_vel
    }

    // Figure out how much distance is left to go
    error = target - current_position;

    // Keep track of how many times this has looped
    step++;
    // delay(whatever);
  }

  // If target is unattainable by a perfect increment, set the final destination here
  if (current_position != target) {
    current_position = target;
    std::cout << step << "\t" << increment << "\n";
  } else {
    std::cout << step << "\t" << increment << "\n";
  }
}

int main() {
  profile(180);
  // std::cout << "Hello World" << std::endl;
}