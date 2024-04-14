// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseDrone.h"

#include "Kismet/GameplayStatics.h"

#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"

#include "InputActionValue.h"

#include "../../Components/CPP_HealthComponent.h"
#include "../../Projectile/CPP_Projectile.h"

// Sets default values
ACPP_BaseDrone::ACPP_BaseDrone()
{
	FrameDrone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame Dron Mesh Component"));
	RootComponent = FrameDrone;

	// Attach Sphere Component
	SphereComponent->SetupAttachment(FrameDrone);

	// Propelers
	FrontLeftPropeler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front Left Propeler Mesh Component"));
	FrontLeftPropeler->SetupAttachment(FrameDrone);

	FrontRightPropeler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front Right Propeler Mesh Component"));
	FrontRightPropeler->SetupAttachment(FrameDrone);

	BackLeftPropeler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Back Left Propeler Mesh Component"));
	BackLeftPropeler->SetupAttachment(FrameDrone);
	
	BackRightPropeler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Back Right Propeler Mesh Component"));
	BackRightPropeler->SetupAttachment(FrameDrone);

	// Create a camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(FrameDrone);

	// Attach ProjectileSpawnPoint
	ProjectileSpawnPoint->SetupAttachment(FrameDrone);
	 
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_BaseDrone::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACPP_BaseDrone::StartShooting(const FInputActionValue& Value)
{
	if (CanShoot)
	{
		Shoot();

		CanShoot = false;

		GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ACPP_BaseDrone::EndShoot, FireRate, true);
	}
}

void ACPP_BaseDrone::EndShooting(const FInputActionValue& Value)
{
	EndShoot();
}



// Called every frame
void ACPP_BaseDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_BaseDrone::Shoot()
{
	if (CountAmmo > 0)
	{
		CountAmmo--;
		OnShootDelegate.Broadcast(CountAmmo);
		
		Super::Shoot();
	}
}
