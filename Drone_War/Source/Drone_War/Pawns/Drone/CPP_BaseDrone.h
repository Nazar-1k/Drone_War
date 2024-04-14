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
	virtual void Move(const FInputActionValue& Value) {};

	/** Called for End Move input */
	virtual void EndMove(const FInputActionValue& Value) {};

	/** Called for movement input */
	virtual void MoveUp(const FInputActionValue& Value) {};

	/** Called for looking input */
	virtual void Look(const FInputActionValue& Value) {};

	virtual void MoveYaw(const FInputActionValue& Value) {};
	virtual void EndMoveYaw(const FInputActionValue& Value) {};

	/** Called for start Shooting input */
	virtual void StartShooting(const FInputActionValue& Value);

	/** Called for end Shooting input */
	virtual void EndShooting(const FInputActionValue& Value);

public:
	
	FORCEINLINE UStaticMeshComponent* GetFrameDrone() { return FrameDrone;};

protected:

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
};
