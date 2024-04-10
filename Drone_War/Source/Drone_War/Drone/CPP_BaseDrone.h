// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_BaseDrone.generated.h"

class UCameraComponent;
class USphereComponent;

class UCPP_HealthComponent;


UCLASS()
class DRONE_WAR_API ACPP_BaseDrone : public APawn
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	/** Base Skeletal Mesh Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;

	/** Camera */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

};
