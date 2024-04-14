// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CPP_BasePawn.h"
#include "CPP_BaseDrone.generated.h"

class UCameraComponent;
class UFloatingPawnMovement;

struct FInputActionValue;
class UInputMappingContext;

UCLASS()
class DRONE_WAR_API ACPP_BaseDrone : public ACPP_BasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_BaseDrone();
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Shoot() override;

public:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for movement input */
	void MoveUp(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for start Shooting input */
	void StartShooting(const FInputActionValue& Value);

	/** Called for end Shooting input */
	void EndShooting(const FInputActionValue& Value);

public:
	
	FORCEINLINE UStaticMeshComponent* GetFrameDrone() { return FrameDrone;};

private:
	/** Frame Drone Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FrameDrone;

	/** Front Left Propeler Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Propelers", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FrontLeftPropeler;

	/** Front Right Propeler Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Propelers", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FrontRightPropeler;

	/** Back Left Propeler Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Propelers", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BackLeftPropeler;

	/** Back Right Propeler Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Propelers", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BackRightPropeler;

	/** Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	/** Floating Pawn Movement */
	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* FloatingPawnMovement;


private:

	/** Drone Speed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Settings", meta = (AllowPrivateAccess = "true"))
	float DroneSpeed = 500.f;

	/** Interpolation Speed Rotating Drone */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drone|Settings", meta = (AllowPrivateAccess = "true"))
	float InterpolationSpeedRotatingDrone = 10.f;
	
private:
	
	/** Rotate Drone to target Rotation with Interpolation */
	void RotateDrone(FRotator TargetRotation);

};
