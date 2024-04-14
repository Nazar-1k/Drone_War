// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseTurret.h"

#include "Components/SphereComponent.h"

ACPP_BaseTurret::ACPP_BaseTurret()
{
	// Turret Mesh Component
	BaseTurret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Turret Mesh Component"));
	RootComponent = BaseTurret;

	RotateTurret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotate Turret Mesh Component"));
	RotateTurret->SetupAttachment(BaseTurret);

	GunTurret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Turret Mesh Component"));
	GunTurret->SetupAttachment(RotateTurret);

	// Attach Sphere Component
	SphereComponent->SetupAttachment(BaseTurret);

	// Attach ProjectileSpawnPoint
	ProjectileSpawnPoint->SetupAttachment(GunTurret);

	PrimaryActorTick.bCanEverTick = true;
}

void ACPP_BaseTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToTargetPosition(DeltaTime);
}

void ACPP_BaseTurret::MoveToTargetPosition(float DeltaTime)
{

	// Get the current rotation angle of the turret around the Z axis for RotateTurret Mesh
	FRotator CurrentRotation = RotateTurret->GetComponentRotation();
	FRotator TargetRotation = (TargetPosition - RotateTurret->GetComponentLocation()).Rotation();
	TargetRotation.Pitch = CurrentRotation.Pitch;
	TargetRotation.Roll = CurrentRotation.Roll;
	TargetRotation.Yaw -= 90; // Problem with mesh

	// Smooth targeting for RotateTurret Mesh
	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);
	RotateTurret->SetWorldRotation(NewRotation);

	FRotator CurrentGunRotation = GunTurret->GetComponentRotation();
	FRotator TargetGunRotation = (TargetPosition - GunTurret->GetComponentLocation()).Rotation();
		

	// Calculate the desired elevation angle (pitch)
	float ElevationAngle = TargetGunRotation.Pitch;

	// Clamp the elevation angle within the desired range
	ElevationAngle = FMath::Clamp(ElevationAngle, MinElevation, MaxElevation);

	// Update the target rotation with the clamped elevation angle
	TargetGunRotation.Roll = -ElevationAngle;

	TargetGunRotation.Yaw = CurrentRotation.Yaw;
	TargetGunRotation.Pitch = CurrentRotation.Pitch;

	FRotator NewGunRotation = FMath::RInterpConstantTo(CurrentGunRotation, TargetGunRotation, DeltaTime, GunRotationSpeed);
	GunTurret->SetWorldRotation(NewGunRotation);
	
}
