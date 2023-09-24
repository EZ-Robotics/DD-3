#include <cmath>
#include <iostream>
using namespace std;

// Constants
const double MAX_VELOCITY = 50.0;
const double MAX_ACCELERATION = 2.0;
const double MAX_DECELERATION = 2.0;

// Return sig of input
int sgn(int input) {
  if (input > 0)
    return 1;
  else if (input < 0)
    return -1;
  return 0;
}

double current_position = 0;

double rad_to_deg(double input) {
  return input * (180.0 / M_PI);
}

void profile(int target) {
  double error = target - current_position;

  int sign = sgn(error);  // Am I going fwd or rev?

  // Fwd vs rev constants
  double max_accel = MAX_ACCELERATION * sign;
  double max_decel = MAX_DECELERATION * sign;
  double max_vel = MAX_VELOCITY * sign;
  double increment = max_accel;  // How much to add each iteration

  double steps_to_accel = (MAX_VELOCITY / MAX_ACCELERATION);
  double steps_to_decel = (MAX_VELOCITY / MAX_DECELERATION);

  // Area under the velocity/time graph for distance traveled
  double dist_to_accel = (steps_to_accel * MAX_VELOCITY) / 2.0;  // Max distance to accelerate
  double dist_to_decel = (steps_to_decel * MAX_VELOCITY) / 2.0;  // Max distance to decelerate
  double steps_to_cruise = 0.0;

  // Check if the motion is large enough that there is cruise time
  if (dist_to_accel + dist_to_decel < fabs(error)) {
    steps_to_cruise = (fabs(error) - (dist_to_accel + dist_to_decel)) / MAX_VELOCITY;  // Distance remaining after accel and decel
  }

  // If there is no cruise time, we have to figure out when to switch accel to decel
  else {
    // Area of the velocity/time graph, aka distance we have to go
    double area = fabs(error);

    // in radians
    double accel_angle = atan2(MAX_ACCELERATION, 1.0);  // Angle between accel/floor
    double decel_angle = atan2(MAX_DECELERATION, 1.0);  // Angle between decel/floor
    double z = M_PI - (accel_angle + decel_angle);      // Angle between accel/decel

    // Solve all angles of the triangle
    double accel_hyp = sqrt(((area * 2.0) * sin(decel_angle)) / ((sin(accel_angle)) * (sin(z))));
    double decel_hyp = sqrt(((area * 2.0) * sin(accel_angle)) / ((sin(decel_angle)) * (sin(z))));
    double z_dist = sqrt(((area * 2.0) * sin(z)) / ((sin(decel_angle)) * (sin(accel_angle))));

    // Find the bottom leg of triangle
    steps_to_accel = cos(accel_angle) * accel_hyp;
    steps_to_decel = cos(decel_angle) * decel_hyp;

    // This is just for double checking above works
    /*
    double calculated_accel_area = ((sqrt(pow(accel_hyp, 2) - pow(steps_to_accel, 2))) * steps_to_accel) / 2.0;
    double calculated_decel_area = ((sqrt(pow(decel_hyp, 2) - pow(steps_to_decel, 2))) * steps_to_decel) / 2.0;
    cout << rad_to_deg(accel_angle) << " " << rad_to_deg(decel_angle) << " " << rad_to_deg(z) << "\n";
    cout << accel_hyp << " " << decel_hyp << "\n";
    cout << steps_to_accel << " " << steps_to_decel << "    " << z_dist << "\n";
    cout << calculated_accel_area + calculated_decel_area << "\n\n";
    */
  }

  // Total steps needed to take
  double total_steps = steps_to_accel + steps_to_decel + steps_to_cruise;

  double decel_b = 0 - (-max_decel * total_steps);  // y intercept for deceleration graph

  std::cout << "Current: " << current_position << "\n";
  std::cout << "Target: " << target << "\n\n";
  std::cout << "Accel Rate: " << max_accel << "\n";
  std::cout << "Decel Rate: " << max_decel << "\n";
  std::cout << "Vel Rate: " << max_vel << "\n\n";
  std::cout << "Steps to Accel: " << steps_to_accel << "\tDist to Accel: " << dist_to_accel << "\n";
  std::cout << "Steps to Decel: " << steps_to_decel << "\tDist to Decel: " << dist_to_decel << "\n";
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
    current_position = fabs(current_position) > fabs(target) ? target : current_position;

    // Decelerating
    if (step >= steps_to_accel + steps_to_cruise) {
      increment = (-max_decel * step) + decel_b;
    }
    // At max vel
    else if (step >= steps_to_accel) {
      increment = max_vel;  // Keep velocity constant, we're at max now
    }
    // Accelerating
    else {
      increment = max_accel * step;
    }

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
  profile(5000);
  // std::cout << "Hello World" << std::endl;
}