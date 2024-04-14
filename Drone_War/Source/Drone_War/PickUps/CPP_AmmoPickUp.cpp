// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AmmoPickUp.h"

#include "../Pawns/Drone/CPP_BaseDrone.h"

void ACPP_AmmoPickUp::WasCollected(ACPP_BasePawn* Drone)
{
	Super::WasCollected(Drone);
	
	Drone->AddAmmo(CountAmmoAdded);
}
