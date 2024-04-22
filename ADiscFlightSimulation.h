// ADiscFlightSimulation.h
// Robert Valentine created the maths and wrote the implementation.
// (Name before marriage: Robert Chubb) 
// (Online Name: SaxonRah)
// (Company Name: Parabolic Labs)
// Creative Commons Attribution-NonCommercial-NoDerivs (Sorry, but this is required).
// All credit goes to him and him alone.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"

#include "ADiscFlightSimulation.generated.h"


UCLASS()
class DISC_API AADiscFlightSimulation : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AADiscFlightSimulation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Setters for initial conditions
	UFUNCTION(BlueprintCallable, Category = "Disc")
	void SetInitialPosition(const FVector& InInitialPosition);

	UFUNCTION(BlueprintCallable, Category = "Disc")
	void SetInitialVelocity(float InInitialVelocity, float InLaunchAngle, float InSpinRate);

	UFUNCTION(BlueprintCallable, Category = "Disc")
	void SetWindForce(const FVector& InWindForce);

	UFUNCTION(BlueprintCallable, Category = "Disc")
	void SetDiscProperties(float InMass, float InDragCoefficient, float InLiftCoefficient, float InFrontalArea, float InDiscStability, float InGyroscopicFactor);

	UFUNCTION(BlueprintCallable, Category = "Disc")
	void Update(float DeltaTime); // Update the simulation

// Calculators

	UFUNCTION(BlueprintCallable, Category = "Disc")
	FVector CalculateTotalForce() const;

	UFUNCTION(BlueprintCallable, Category = "Disc")
	float CalculateLiftForce() const;

private:
// Private Properties
	UPROPERTY(VisibleAnywhere, Category = "Disc|Properties")
	FVector CurrentPosition;
	UPROPERTY(VisibleAnywhere, Category = "Disc|Properties")
	FVector CurrentVelocity;

public: 
// Public Properties
	UPROPERTY(EditAnywhere, Category = "Disc|Properties")
	FVector WindForce;
	UPROPERTY(EditAnywhere, Category = "Disc|Properties")
	float Mass;
	UPROPERTY(EditAnywhere, Category = "Disc|Properties")
	float DragCoefficient;
	UPROPERTY(EditAnywhere, Category = "Disc|Properties")
	float LiftCoefficient;
	UPROPERTY(EditAnywhere, Category = "Disc|Properties")
	float FrontalArea;
	UPROPERTY(EditAnywhere, Category = "Disc|Properties")
	float DiscStability;
	UPROPERTY(EditAnywhere, Category = "Disc|Properties")
	float GyroscopicFactor;

	UPROPERTY(EditAnywhere, Category = "Disc|Properties")
	float SpinRate;
	UPROPERTY(EditAnywhere, Category = "Disc|Properties")
	float LaunchAngle;

	UPROPERTY(EditAnywhere, Category = "Disc|Properties")
	float Gravity = 9.81f; // Acceleration due to gravity
};
