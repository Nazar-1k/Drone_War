// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BasePawn.h"

#include "Components/SphereComponent.h"

#include "../Components/CPP_HealthComponent.h"
#include "../Projectile/CPP_Projectile.h"

// Sets default values
ACPP_BasePawn::ACPP_BasePawn()
{
	// Create ProjectileSpawnPoint
	ProjectileSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawn Point"));

	// Create Sphere Component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	
	// Health Component
	HealthComponent = CreateDefaultSubobject<UCPP_HealthComponent>(TEXT("Health Component"));

	PrimaryActorTick.bCanEverTick = true;
}

void ACPP_BasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_BasePawn::Shoot()
{
	FVector StartLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator RotationAngle = ProjectileSpawnPoint->GetComponentRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	if (UWorld* World = GetWorld())
	{
		World->SpawnActor<ACPP_Projectile>(ProjectileClass, StartLocation, RotationAngle, SpawnParams);
	}
}

void ACPP_BasePawn::EndShoot()
{
	CanShoot = true;
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ACPP_BasePawn::AddAmmo(int32 CountAmmoAdded)
{
	CountAmmo += CountAmmoAdded;
	OnShootDelegate.Broadcast(CountAmmo);
}


