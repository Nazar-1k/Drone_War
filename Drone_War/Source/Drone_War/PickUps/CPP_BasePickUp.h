// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_BasePickUp.generated.h"

class USphereComponent;
class UNiagaraComponent;

class ACPP_BasePawn;

UCLASS()
class DRONE_WAR_API ACPP_BasePickUp : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ACPP_BasePickUp();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Function to call when the pickup is collected */
	virtual void WasCollected(ACPP_BasePawn* Drone);

public:
	/** Return the mesh for the pickup */
	FORCEINLINE UNiagaraComponent* GetNiagaraComponent() const { return NiagaraComponent; }

protected:

	/** Niagara Component to represent the pickup in the level*/
	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponent;

	/** Collection sphere */
	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollectionSphere;

private:

	UFUNCTION()
	void CollectPickups(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
