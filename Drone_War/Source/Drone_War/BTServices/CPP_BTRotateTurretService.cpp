// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BTRotateTurretService.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "../Pawns/Turret/CPP_BaseTurret.h"
#include "../Pawns/Drone/CPP_BaseDrone.h"
#include "../Components/CPP_HealthComponent.h"

UCPP_BTRotateTurretService::UCPP_BTRotateTurretService()
{
	NodeName = "Update Rotate Turret";
}

void UCPP_BTRotateTurretService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (ACPP_BaseDrone* TargetDrone = Cast<ACPP_BaseDrone>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor")))
	{
		if (ACPP_BaseTurret* Turret = Cast<ACPP_BaseTurret>(OwnerComp.GetAIOwner()->GetPawn()))
		{
			if (!TargetDrone->GetHealthComponent()->IsDie())
			{
				Turret->SetTargetPosition(TargetDrone->GetActorLocation());
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->ClearValue("TargetActor");
			}
		}
	}
}
