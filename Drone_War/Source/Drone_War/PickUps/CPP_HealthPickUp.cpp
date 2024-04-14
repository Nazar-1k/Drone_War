// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_HealthPickUp.h"

#include "../Pawns/Drone/CPP_BaseDrone.h"
#include "../Components/CPP_HealthComponent.h"

void ACPP_HealthPickUp::WasCollected(ACPP_BasePawn* Drone)
{
	if (UCPP_HealthComponent* HPComponent = Drone->GetHealthComponent())
	{
		if (!HPComponent->IsDie() && (HPComponent->GetCurrentHealth() < HPComponent->GetMaxHealth()))
		{
			HPComponent->AddHealh(CountHealthAdd);
			Super::WasCollected(Drone);
		}
	}
}
