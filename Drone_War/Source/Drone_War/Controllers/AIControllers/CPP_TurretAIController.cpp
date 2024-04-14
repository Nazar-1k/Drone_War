// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TurretAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../../Pawns/Turret/CPP_BaseTurret.h"


ACPP_TurretAIController::ACPP_TurretAIController()
{
	PerceptionFollowComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Follow")); 

	SightFollow = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Follow"));

	SightFollow->SightRadius = SightRadius;
	SightFollow->LoseSightRadius = LoseSightRadius;
	SightFollow->PeripheralVisionAngleDegrees = PeripheralVisionAngleDegrees;
	SightFollow->DetectionByAffiliation.bDetectNeutrals = true;

	
	PerceptionFollowComponent->ConfigureSense(*SightFollow);
	PerceptionFollowComponent->SetDominantSense(SightFollow->GetSenseImplementation());
}


void ACPP_TurretAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBahaviorTree)
	{
		RunBehaviorTree(AIBahaviorTree);
	}

}

void ACPP_TurretAIController::OnPerceptionFollow(AActor* Actor, FAIStimulus Stimulus)
{
	if (ACPP_BaseTurret* OtherEnemy = Cast<ACPP_BaseTurret>(Actor))	{ return; }

	if (Stimulus.WasSuccessfullySensed())
	{
		
		GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), Actor);
	}
	else
	{
		GetBlackboardComponent()->ClearValue(FName("TargetActor"));
	}
}

void ACPP_TurretAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

	PerceptionFollowComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ACPP_TurretAIController::OnPerceptionFollow);
}
