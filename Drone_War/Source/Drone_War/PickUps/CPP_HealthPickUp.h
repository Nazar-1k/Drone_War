// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CPP_BasePickUp.h"
#include "CPP_HealthPickUp.generated.h"


class ACPP_BaseDrone;

UCLASS()
class DRONE_WAR_API ACPP_HealthPickUp : public ACPP_BasePickUp
{
	GENERATED_BODY()
	
public:
	
	void WasCollected(ACPP_BasePawn* Drone) override;


private:
	
	float CountHealthAdd = 40.f;

};
