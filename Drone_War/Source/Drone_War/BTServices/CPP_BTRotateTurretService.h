// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CPP_BTRotateTurretService.generated.h"

/**
 * 
 */
UCLASS()
class DRONE_WAR_API UCPP_BTRotateTurretService : public UBTService
{
	GENERATED_BODY()

public:

	UCPP_BTRotateTurretService();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
