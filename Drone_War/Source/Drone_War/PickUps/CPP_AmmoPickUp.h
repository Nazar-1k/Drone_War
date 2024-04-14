// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BasePickUp.h"
#include "CPP_AmmoPickUp.generated.h"

/**
 * 
 */
UCLASS()
class DRONE_WAR_API ACPP_AmmoPickUp : public ACPP_BasePickUp
{
	GENERATED_BODY()

public:

	void WasCollected(ACPP_BasePawn* Drone) override;

private:
	UPROPERTY(EditAnywhere)
	int32 CountAmmoAdded = 5;

};
