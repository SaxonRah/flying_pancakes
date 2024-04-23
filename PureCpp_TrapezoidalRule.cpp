#include <iostream>
#include <cmath>

// Constants
const double g = 9.81;  // Acceleration due to gravity

// Function to calculate position at time t using trapezoidal rule
double calculatePosition(double v0, double theta,
                         double Cd, double Cl, double A,
                         double wind_x, double wind_y, double wind_z,
                         double S, double SpinRate, double GyroscopicFactor,
                         double m, double rho,
                         double t) {
    // Calculate initial velocity components
    double v0x = v0 * sin(theta);
    double v0y = v0 * cos(theta);
    double v0z = v0 * sin(theta);

    // Initialize variables for trapezoidal integration
    double dt = 0.001;  // Time step for integration
    double integral_x = 0.0, integral_y = 0.0, integral_z = 0.0;

    // Calculate position using trapezoidal rule for integration
    for (double tau = 0; tau <= t; tau += dt) {
        // Calculate total forces
        double F_total_x = -0.5 * rho * Cd * A * pow(sqrt(pow(v0x - wind_x, 2) + pow(v0y - wind_y, 2) + pow(v0z - wind_z, 2)), 2);
        double F_total_y = -0.5 * rho * Cd * A * pow(sqrt(pow(v0x - wind_x, 2) + pow(v0y - wind_y, 2) + pow(v0z - wind_z, 2)), 2);
        double F_total_z = m * g - 0.5 * rho * Cd * A * pow(sqrt(pow(v0x - wind_x, 2) + pow(v0y - wind_y, 2) + pow(v0z - wind_z, 2)), 2);

        // Calculate lift force
        double F_lift_z = 0.5 * Cl * A * rho * sqrt(pow(v0x - wind_x, 2) + pow(v0y - wind_y, 2) + pow(v0z - wind_z, 2)) * SpinRate * GyroscopicFactor * S;

        // Integrate forces
        integral_x += (F_total_x / m) * dt;
        integral_y += (F_total_y / m) * dt;
        integral_z += (F_total_z / m + F_lift_z) * dt;
    }

    // Calculate final position
    double z = v0z * t - 0.5 * g * t * t + integral_z;

    return z;
}

int main() {
    // Test the function
    double v0 = 20;  // Initial velocity
    double theta = M_PI / 4;  // Launch angle (45 degrees)
    double Cd = 0.5;  // Drag coefficient
    double Cl = 0.1;  // Lift coefficient
    double A = 0.01;  // Frontal area
    double wind_x = 0, wind_y = 0, wind_z = 0;  // No wind
    double S = 1;  // Disc stability factor
    double SpinRate = 100;  // Spin rate of the disc
    double GyroscopicFactor = 0.1;  // Gyroscopic factor
    double m = 0.2;  // Mass of the disc
    double rho = 1.225;  // Air density

    double t = 1;  // Time

    // Calculate position at time t from initial position 0x0y0z
    double z_from_origin = calculatePosition(v0, theta, Cd, Cl, A, wind_x, wind_y, wind_z, S, SpinRate, GyroscopicFactor, m, rho, t);

    // Calculate position at time t from initial position 1000x1000y800z
    double z_from_high_position = calculatePosition(v0, theta, Cd, Cl, A, wind_x, wind_y, wind_z, S, SpinRate, GyroscopicFactor, m, rho, t);

    // Output the results
    std::cout << "Position at time " << t << " seconds from origin: " << z_from_origin << " meters" << std::endl;
    std::cout << "Position at time " << t << " seconds from high position: " << z_from_high_position << " meters" << std::endl;

    return 0;
}
