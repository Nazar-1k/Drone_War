// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BTShootTaskNode.h"

#include "../Pawns/Turret/CPP_BaseTurret.h"

#include "AIController.h"

UCPP_BTShootTaskNode::UCPP_BTShootTaskNode()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UCPP_BTShootTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	ACPP_BaseTurret* Enemy = Cast<ACPP_BaseTurret>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Enemy)
	{
		return EBTNodeResult::Failed;
	}

	Enemy->Shoot();

	return EBTNodeResult::Succeeded;

}
