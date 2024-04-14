// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_BasePawn.generated.h"

class USphereComponent;
class UCPP_HealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShootSignature, int32, CountAmmo);

UCLASS()
class DRONE_WAR_API ACPP_BasePawn : public APawn
{
	GENERATED_BODY()

public:

	ACPP_BasePawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	virtual void Shoot();
	virtual void EndShoot();

public:

	UPROPERTY(BlueprintAssignable)
	FOnShootSignature OnShootDelegate;

public:

	FORCEINLINE bool IsLoose() { return bLoose; }
	FORCEINLINE UCPP_HealthComponent* GetHealthComponent() { return HealthComponent; }
	FORCEINLINE int32 GetCountAmmo() { return CountAmmo; }

	void AddAmmo(int32 CountAmmoAdded);

protected:

	/** Health Component */
	UPROPERTY(EditAnywhere, Category = "Components")
	UCPP_HealthComponent* HealthComponent;

	/** True if you Loose */
	bool bLoose = false;

	/** Shot Range */
	UPROPERTY(EditAnywhere, Category = "Settings|Shoot")
	float FireRate = 0.5f;

	/** Count Ammo */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings|Shoot", meta = (AllowPrivateAccess = "true"))
	int32 CountAmmo = 10;

	bool CanShoot = true;
	FTimerHandle ShotTimerHandle;

protected:

	/** Base Skeletal Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;

	/** Actor Class for Projectile */
	UPROPERTY(EditAnywhere, Category = "Settings|Projectile", meta = (AllowPrivateAccess = "true"))
	class UClass* ProjectileClass;

	/** Projectile Spawn Point */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

};
