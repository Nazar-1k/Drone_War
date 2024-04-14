// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BTClearBlackboardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UCPP_BTClearBlackboardValue::UCPP_BTClearBlackboardValue()
{
	NodeName = "Clear Blackboard Value";
}

EBTNodeResult::Type UCPP_BTClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}