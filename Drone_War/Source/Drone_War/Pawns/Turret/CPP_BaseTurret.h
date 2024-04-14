// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CPP_BasePawn.h"
#include "CPP_BaseTurret.generated.h"

/**
 * 
 */
UCLASS()
class DRONE_WAR_API ACPP_BaseTurret : public ACPP_BasePawn
{
	GENERATED_BODY()

public:

	ACPP_BaseTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void SetTargetPosition(FVector NewTargetPosition) { TargetPosition = NewTargetPosition; };

public:

	FORCEINLINE UStaticMeshComponent* GetBaseTurret() { return BaseTurret; };
	FORCEINLINE UStaticMeshComponent* GetRotateTurret() { return RotateTurret; };
	FORCEINLINE UStaticMeshComponent* GetGunTurret() { return GunTurret; };

protected:

	/** Base Turret Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseTurret;

	/** Rotate Turret Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RotateTurret;

	/** Gun Turret Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GunTurret;

	FVector TargetPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float RotationSpeed = 70.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float GunRotationSpeed = 25.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float MinElevation = -205.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float MaxElevation = 25.f;


private:
	
	void MoveToTargetPosition(float DeltaTime);
};
