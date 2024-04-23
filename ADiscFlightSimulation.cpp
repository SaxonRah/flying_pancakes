// ADiscFlightSimulation.cpp
// Robert Valentine created the maths and wrote the implementation.
// (Name before marriage: Robert Chubb) 
// (Online Name: SaxonRah)
// (Company Name: Parabolic Labs)
// Creative Commons Attribution-NonCommercial-NoDerivs (Sorry, but this is required).
// All credit goes to him and him alone.

#include "ADiscFlightSimulation.h"

// Sets default values
AADiscFlightSimulation::AADiscFlightSimulation()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

        // Initialize variables
    this->CurrentPosition = FVector::ZeroVector;
    this->CurrentVelocity = FVector::ZeroVector;
    this->WindForce = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void AADiscFlightSimulation::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AADiscFlightSimulation::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update
    Update(DeltaTime);
}

void AADiscFlightSimulation::SetInitialPosition(const FVector& InInitialPosition)
{
    this->CurrentPosition = InInitialPosition;
}

void AADiscFlightSimulation::SetInitialVelocity(float InInitialVelocity, float InLaunchAngle, float InSpinRate)
{
    this->LaunchAngle = InLaunchAngle;
    this->SpinRate = InSpinRate;

    float LaunchAngleRadians = FMath::DegreesToRadians(InLaunchAngle);
    this->CurrentVelocity.X = InInitialVelocity * FMath::Sin(LaunchAngleRadians);
    this->CurrentVelocity.Y = InInitialVelocity * FMath::Cos(LaunchAngleRadians);
    this->CurrentVelocity.Z = InInitialVelocity * FMath::Sin(LaunchAngleRadians);
}

void AADiscFlightSimulation::SetWindForce(const FVector& InWindForce)
{
    this->WindForce = InWindForce;
}

void AADiscFlightSimulation::SetDiscProperties(float InMass, float InDragCoefficient, float InLiftCoefficient, float InFrontalArea, float InDiscStability, float InGyroscopicFactor)
{
    this->Mass = InMass;
    this->DragCoefficient = InDragCoefficient;
    this->LiftCoefficient = InLiftCoefficient;
    this->FrontalArea = InFrontalArea;
    this->DiscStability = InDiscStability;
    this->GyroscopicFactor = InGyroscopicFactor;
}

void AADiscFlightSimulation::Update(float DeltaTime)
{
    // Calculate total force and lift force at the current position
    FVector TotalForce = CalculateTotalForce();
    float LiftForce = CalculateLiftForce();

    // Store old position and velocity for trapezoidal rule
    FVector OldPosition = this->CurrentPosition;
    FVector OldVelocity = this->CurrentVelocity;

    // Update velocity using forces at the old position
    FVector Acceleration = TotalForce / this->Mass;
    this->CurrentVelocity += 0.5f * (Acceleration + (TotalForce / this->Mass)) * DeltaTime;

    // Include lift force in position update
    FVector LiftAcceleration = FVector(0, 0, LiftForce) / this->Mass; // Lift force only affects z-axis acceleration
    this->CurrentPosition += 0.5f * (OldVelocity + this->CurrentVelocity) * DeltaTime;
    this->CurrentVelocity.Z += 0.5f * (LiftAcceleration.Z + LiftAcceleration.Z) * DeltaTime; // Update z-velocity using lift force
}

FVector AADiscFlightSimulation::CalculateTotalForce() const
{
    FVector TotalForce;

    // Calculate drag force
    float VelocitySquared = this->CurrentVelocity.SizeSquared();
    FVector DragForce = -0.5f * this->DragCoefficient * this->FrontalArea * VelocitySquared * this->CurrentVelocity.GetSafeNormal();

    // Calculate total force including wind
    TotalForce = DragForce + this->WindForce;

    return TotalForce;
}

float AADiscFlightSimulation::CalculateLiftForce() const
{
    // Calculate lift force
    float LiftForce = 0.5f * this->LiftCoefficient * this->FrontalArea * this->Gravity * this->SpinRate * this->GyroscopicFactor * this->DiscStability;
    return LiftForce;
}
