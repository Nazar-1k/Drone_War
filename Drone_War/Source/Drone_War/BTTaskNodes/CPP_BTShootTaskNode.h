// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CPP_BTShootTaskNode.generated.h"

UCLASS()
class DRONE_WAR_API UCPP_BTShootTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UCPP_BTShootTaskNode();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
