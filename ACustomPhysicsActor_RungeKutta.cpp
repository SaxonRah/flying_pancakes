// Robert Valentine created the maths and wrote the implementation.
// (Name before marriage: Robert Chubb) 
// (Online Name: SaxonRah)
// (Company Name: Parabolic Labs)
// Creative Commons Attribution-NonCommercial-NoDerivs (Sorry, but this is required).
// All credit goes to him and him alone.

#include "CustomPhysicsActor.h"

// Constructor
ACustomPhysicsActor::ACustomPhysicsActor()
{
    // Set default values for parameters
    InitialVelocity = 20;  // Initial velocity
    LaunchAngle = PI / 4;   // Launch angle (45 degrees)
    Cd = 0.5;               // Drag coefficient
    Cl = 0.1;               // Lift coefficient
    A = 0.01;               // Frontal area
    WindVector = FVector(0, 0, 0); // No wind
    S = 1;                  // Disc stability factor
    SpinRate = 100;         // Spin rate of the disc
    GyroscopicFactor = 0.1; // Gyroscopic factor
    Mass = 0.2;             // Mass of the disc
    AirDensity = 1.225;     // Air density
    TimeStep = 0.001;       // Time step
}

// Function to calculate total forces
void ACustomPhysicsActor::CalculateForces(FVector Velocity, float& F_total_x, float& F_total_y, float& F_total_z)
{
    // Calculate total forces
    F_total_x = -0.5f * AirDensity * Cd * A * pow(sqrt(pow(Velocity.X - WindVector.X, 2) + pow(Velocity.Y - WindVector.Y, 2) + pow(Velocity.Z - WindVector.Z, 2)), 2);
    F_total_y = -0.5f * AirDensity * Cd * A * pow(sqrt(pow(Velocity.X - WindVector.X, 2) + pow(Velocity.Y - WindVector.Y, 2) + pow(Velocity.Z - WindVector.Z, 2)), 2);
    F_total_z = Mass * g - 0.5f * AirDensity * Cd * A * pow(sqrt(pow(Velocity.X - WindVector.X, 2) + pow(Velocity.Y - WindVector.Y, 2) + pow(Velocity.Z - WindVector.Z, 2)), 2);
}

// Function to perform Runge-Kutta 4th order integration
FVector ACustomPhysicsActor::RungeKuttaIntegration(FVector Velocity, float t)
{
    // Initialize variables
    FVector k1, k2, k3, k4;

    // Calculate k1
    float F_total_x, F_total_y, F_total_z;
    CalculateForces(Velocity, F_total_x, F_total_y, F_total_z);
    k1.X = (F_total_x / Mass) * TimeStep;
    k1.Y = (F_total_y / Mass) * TimeStep;
    k1.Z = (F_total_z / Mass) * TimeStep;

    // Calculate k2
    CalculateForces(Velocity + k1 * 0.5f, F_total_x, F_total_y, F_total_z);
    k2.X = (F_total_x / Mass) * TimeStep;
    k2.Y = (F_total_y / Mass) * TimeStep;
    k2.Z = (F_total_z / Mass) * TimeStep;

    // Calculate k3
    CalculateForces(Velocity + k2 * 0.5f, F_total_x, F_total_y, F_total_z);
    k3.X = (F_total_x / Mass) * TimeStep;
    k3.Y = (F_total_y / Mass) * TimeStep;
    k3.Z = (F_total_z / Mass) * TimeStep;

    // Calculate k4
    CalculateForces(Velocity + k3, F_total_x, F_total_y, F_total_z);
    k4.X = (F_total_x / Mass) * TimeStep;
    k4.Y = (F_total_y / Mass) * TimeStep;
    k4.Z = (F_total_z / Mass) * TimeStep;

    // Update velocity using weighted sum of k values
    FVector NewVelocity = Velocity + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

    // Calculate new position using updated velocity
    FVector NewPosition = GetActorLocation() + NewVelocity * TimeStep;

    // Set new actor location
    SetActorLocation(NewPosition);

    return NewVelocity;
}

// Called every frame
void ACustomPhysicsActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Initialize velocity vector
    FVector Velocity = FVector(InitialVelocity * sin(LaunchAngle), InitialVelocity * cos(LaunchAngle), InitialVelocity * sin(LaunchAngle));

    // Perform Runge-Kutta integration
    Velocity = RungeKuttaIntegration(Velocity, DeltaTime);
}
