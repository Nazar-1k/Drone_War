// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseDrone.h"

#include "Kismet/GameplayStatics.h"

#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
ACPP_BaseDrone::ACPP_BaseDrone()
{
	FrameDrone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame Dron Mesh Component"));
	RootComponent = FrameDrone;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
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

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_BaseDrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_BaseDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_BaseDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
