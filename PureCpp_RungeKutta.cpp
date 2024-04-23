#include <iostream>
#include <cmath>

// Constants
const double g = 9.81;  // Acceleration due to gravity

// Function to calculate total forces
void calculateForces(double v0x, double v0y, double v0z,
                     double Cd, double Cl, double A,
                     double wind_x, double wind_y, double wind_z,
                     double S, double SpinRate, double GyroscopicFactor,
                     double m, double rho,
                     double& F_total_x, double& F_total_y, double& F_total_z) {
    // Calculate total forces
    F_total_x = -0.5 * rho * Cd * A * pow(sqrt(pow(v0x - wind_x, 2) + pow(v0y - wind_y, 2) + pow(v0z - wind_z, 2)), 2);
    F_total_y = -0.5 * rho * Cd * A * pow(sqrt(pow(v0x - wind_x, 2) + pow(v0y - wind_y, 2) + pow(v0z - wind_z, 2)), 2);
    F_total_z = m * g - 0.5 * rho * Cd * A * pow(sqrt(pow(v0x - wind_x, 2) + pow(v0y - wind_y, 2) + pow(v0z - wind_z, 2)), 2);
}

// Function to perform Runge-Kutta 4th order integration
double rungeKuttaIntegration(double v0x, double v0y, double v0z,
                             double Cd, double Cl, double A,
                             double wind_x, double wind_y, double wind_z,
                             double S, double SpinRate, double GyroscopicFactor,
                             double m, double rho,
                             double t, double dt) {
    // Initialize variables
    double k1x, k1y, k1z;
    double k2x, k2y, k2z;
    double k3x, k3y, k3z;
    double k4x, k4y, k4z;

    // Calculate k1
    double F_total_x, F_total_y, F_total_z;
    calculateForces(v0x, v0y, v0z, Cd, Cl, A, wind_x, wind_y, wind_z, S, SpinRate, GyroscopicFactor, m, rho, F_total_x, F_total_y, F_total_z);
    k1x = (F_total_x / m) * dt;
    k1y = (F_total_y / m) * dt;
    k1z = (F_total_z / m) * dt;

    // Calculate k2
    calculateForces(v0x + k1x / 2, v0y + k1y / 2, v0z + k1z / 2, Cd, Cl, A, wind_x, wind_y, wind_z, S, SpinRate, GyroscopicFactor, m, rho, F_total_x, F_total_y, F_total_z);
    k2x = (F_total_x / m) * dt;
    k2y = (F_total_y / m) * dt;
    k2z = (F_total_z / m) * dt;

    // Calculate k3
    calculateForces(v0x + k2x / 2, v0y + k2y / 2, v0z + k2z / 2, Cd, Cl, A, wind_x, wind_y, wind_z, S, SpinRate, GyroscopicFactor, m, rho, F_total_x, F_total_y, F_total_z);
    k3x = (F_total_x / m) * dt;
    k3y = (F_total_y / m) * dt;
    k3z = (F_total_z / m) * dt;

    // Calculate k4
    calculateForces(v0x + k3x, v0y + k3y, v0z + k3z, Cd, Cl, A, wind_x, wind_y, wind_z, S, SpinRate, GyroscopicFactor, m, rho, F_total_x, F_total_y, F_total_z);
    k4x = (F_total_x / m) * dt;
    k4y = (F_total_y / m) * dt;
    k4z = (F_total_z / m) * dt;

    // Update position using weighted sum of k values
    double x = v0x + (k1x + 2 * k2x + 2 * k3x + k4x) / 6;
    double y = v0y + (k1y + 2 * k2y + 2 * k3y + k4y) / 6;
    double z = v0z + (k1z + 2 * k2z + 2 * k3z + k4z) / 6;

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
    double dt = 0.001;  // Time step

    // Calculate position at time t using Runge-Kutta 4th order integration
    double z = rungeKuttaIntegration(v0 * sin(theta), v0 * cos(theta), v0 * sin(theta),
                                     Cd, Cl, A, wind_x, wind_y, wind_z, S, SpinRate, GyroscopicFactor, m, rho, t, dt);

    // Output the result
    std::cout << "Position at time " << t << " seconds: " << z << " meters" << std::endl;

    return 0;
}
