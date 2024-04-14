// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CPP_EngineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONE_WAR_API UCPP_EngineComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_EngineComponent();

	void AddUpForce(float Force);
	void AddYawForce(float Force);

	FORCEINLINE void SetClockwise(bool bClockwise) { IsClockwise = bClockwise; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ApllyForses(float DeltaTime);
	void ApllyForce(FVector ForceAmount);

	void DrawDebugForce(FVector ForceAmount, FVector ForceLocation);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	float UpForcePerTick;
	float YawForcePerTick;
	
	bool IsClockwise;
	

private:
	UPrimitiveComponent* PhysicsBody;

};
