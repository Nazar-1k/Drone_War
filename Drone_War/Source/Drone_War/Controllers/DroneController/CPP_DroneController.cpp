// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DroneController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "../../Pawns/Drone/CPP_BaseDrone.h"

void ACPP_DroneController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		OwnedCharacter->EnableInput(this);
		EnableInput(this);
	}
	else
	{
		OwnedCharacter->DisableInput(this);
		DisableInput(this);
	}

	bShowMouseCursor = bPlayerEnabled;
}

void ACPP_DroneController::BeginPlay()
{
	SetupInputMappingContext();

	OwnedCharacter = Cast<ACPP_BaseDrone>(GetPawn());

	// Call again when we have OwnedCharacter
	SetupInputComponent();
}

void ACPP_DroneController::SetupInputComponent()
{
	if (OwnedCharacter)
	{
		Super::SetupInputComponent();

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			// Moving
			if (MoveAction)
			{
				EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, OwnedCharacter, &ACPP_BaseDrone::Move);
				EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, OwnedCharacter, &ACPP_BaseDrone::EndMove);
			}
			if (MoveUpAction)
			{
				EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Triggered, OwnedCharacter, &ACPP_BaseDrone::MoveUp);
			}

			// Looking
			if(LookAction)
			{
				EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, OwnedCharacter, &ACPP_BaseDrone::Look);
			}
			
			// Shooting
			if (ShootAction)
			{
				EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, OwnedCharacter, &ACPP_BaseDrone::StartShooting);
				EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, OwnedCharacter, &ACPP_BaseDrone::EndShooting);
			}

			// Move Yaw
			if (ShootAction)
			{
				EnhancedInputComponent->BindAction(MoveYaw, ETriggerEvent::Triggered, OwnedCharacter, &ACPP_BaseDrone::MoveYaw);
				EnhancedInputComponent->BindAction(MoveYaw, ETriggerEvent::Completed, OwnedCharacter, &ACPP_BaseDrone::EndMoveYaw);
			}
		}
	}
}

void ACPP_DroneController::SetupInputMappingContext()
{
	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}
