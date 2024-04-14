// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_HealthPickUp.h"

#include "../Pawns/Drone/CPP_BaseDrone.h"
#include "../Components/CPP_HealthComponent.h"

void ACPP_HealthPickUp::WasCollected(ACPP_BasePawn* Drone)
{
	Super::WasCollected(Drone);

	if (UCPP_HealthComponent* HPComponent = Drone->GetHealthComponent())
	{
		HPComponent->AddHealh(CountHealthAdd);
	}
}
