// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_SimpleDrone.h"

#include "Kismet/GameplayStatics.h"

#include "InputActionValue.h"

#include "GameFramework/FloatingPawnMovement.h"

ACPP_SimpleDrone::ACPP_SimpleDrone()
{
	// Movment Component
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void ACPP_SimpleDrone::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.X * DroneSpeed);
		AddMovementInput(GetActorRightVector(), MovementVector.Y * DroneSpeed);
	}
}

void ACPP_SimpleDrone::MoveUp(const FInputActionValue& Value)
{
	float MovementVector = Value.Get<float>();

	AddMovementInput(GetActorUpVector(), MovementVector * DroneSpeed);
}

void ACPP_SimpleDrone::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);

		RotateDrone(GetControlRotation());
	}
}

void ACPP_SimpleDrone::RotateDrone(FRotator TargetRotation)
{
	FRotator TurretWorldRotation = FrameDrone->GetComponentRotation();
	FRotator TurretRelativeRotation = FrameDrone->GetRelativeRotation();

	float YawDifference = TargetRotation.Yaw - TurretWorldRotation.Yaw;
	float RollDifference = TargetRotation.Roll - TurretWorldRotation.Roll;

	TurretRelativeRotation.Yaw += YawDifference;
	TurretRelativeRotation.Roll += RollDifference;

	FrameDrone->SetRelativeRotation(FMath::RInterpTo(
		FrameDrone->GetRelativeRotation(),
		TurretRelativeRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this), InterpolationSpeedRotatingDrone));
}
