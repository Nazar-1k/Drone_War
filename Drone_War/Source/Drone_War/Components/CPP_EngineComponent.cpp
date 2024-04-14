// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EngineComponent.h"

// Sets default values for this component's properties
UCPP_EngineComponent::UCPP_EngineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCPP_EngineComponent::BeginPlay()
{
	Super::BeginPlay();

	PhysicsBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
}

void UCPP_EngineComponent::ApllyForses(float DeltaTime)
{
	// Up Force
	float pUpFarce = UpForcePerTick * DeltaTime;
	
	FVector UpForceAmount = pUpFarce * GetUpVector();
	
	
	ApllyForce(UpForceAmount);

	// Yaw Force
	float pYawFarce = YawForcePerTick * DeltaTime;

	FRotator EngineRotation = GetRelativeRotation();
	EngineRotation.Yaw += 45;

	FVector YawForce = pYawFarce * EngineRotation.RotateVector(GetRightVector());

	if (IsClockwise)
	{
		ApllyForce(YawForce);
	}
	else
	{
		ApllyForce(-YawForce);
	}

	UpForcePerTick = 0;
	YawForcePerTick = 0;
}

void UCPP_EngineComponent::ApllyForce(FVector ForceAmount)
{
	PhysicsBody->AddForceAtLocation(ForceAmount, GetComponentLocation());

	// Temp
	DrawDebugForce(ForceAmount, GetComponentLocation());
}

void UCPP_EngineComponent::DrawDebugForce(FVector ForceAmount, FVector ForceLocation)
{
	FVector LineStart = ForceLocation;
	FVector LineEnd = ForceLocation + ForceAmount;
	FColor LineColor = FColor::Green;

	DrawDebugLine(GetWorld(), LineStart, LineEnd, LineColor);
}

void UCPP_EngineComponent::AddUpForce(float Force)
{
	UpForcePerTick += Force;
}

void UCPP_EngineComponent::AddYawForce(float Force)
{
	YawForcePerTick += Force;
}

// Called every frame
void UCPP_EngineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	ApllyForses(DeltaTime);
}
