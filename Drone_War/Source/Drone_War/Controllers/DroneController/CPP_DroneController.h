// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_DroneController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class ACPP_BaseDrone;

UCLASS()
class DRONE_WAR_API ACPP_DroneController : public APlayerController
{
	GENERATED_BODY()
public:

	void SetPlayerEnabledState(bool bPlayerEnabled);

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void SetupInputMappingContext();


	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|MappingContext")
	UInputMappingContext* InputMappingContext;

private:

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action" , meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Move Up Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveUpAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveYaw;

	ACPP_BaseDrone* OwnedCharacter;

};
