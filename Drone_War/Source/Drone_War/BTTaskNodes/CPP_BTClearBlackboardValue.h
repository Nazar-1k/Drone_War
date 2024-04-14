// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CPP_BTClearBlackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class DRONE_WAR_API UCPP_BTClearBlackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UCPP_BTClearBlackboardValue();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
