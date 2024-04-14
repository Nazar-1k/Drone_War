// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseDrone.h"
#include "CPP_SimpleDrone.generated.h"

struct FInputActionValue;
class UInputMappingContext;

UCLASS()
class DRONE_WAR_API ACPP_SimpleDrone : public ACPP_BaseDrone
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_SimpleDrone();

public:

	/** Called for movement input */
	void Move(const FInputActionValue& Value) override;

	/** Called for movement input */
	void MoveUp(const FInputActionValue& Value) override;

	/** Called for looking input */
	void Look(const FInputActionValue& Value) override;

private:

	/** Drone Speed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Settings", meta = (AllowPrivateAccess = "true"))
	float DroneSpeed = 500.f;

	/** Interpolation Speed Rotating Drone */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Settings", meta = (AllowPrivateAccess = "true"))
	float InterpolationSpeedRotatingDrone = 10.f;

private:
	/** Floating Pawn Movement */
	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* FloatingPawnMovement;

	
private:

	/** Rotate Drone to target Rotation with Interpolation */
	void RotateDrone(FRotator TargetRotation);

};
