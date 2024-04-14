// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_HealthComponent.h"

#include "Kismet/GameplayStatics.h"

#include "../Pawns/Drone/CPP_BaseDrone.h"

#include "../Controllers/DroneController/CPP_DroneController.h"

// Sets default values for this component's properties
UCPP_HealthComponent::UCPP_HealthComponent()
{
	CurrentHealth = MaxHealth;
}


void UCPP_HealthComponent::AddHealh(float AddedHealth)
{
	if (AddedHealth <= 0) return;

	CurrentHealth = FMath::Clamp(CurrentHealth + AddedHealth, 0, MaxHealth);
	OnHealthChangedDelegate.Broadcast(CurrentHealth);
}

// Called when the game starts
void UCPP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UCPP_HealthComponent::DamageTaken);
}

void UCPP_HealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

	if (Damage == 0.0f) return;
	
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0, MaxHealth);
	
	OnHealthChangedDelegate.Broadcast(CurrentHealth);

	if (CurrentHealth == 0)
	{
		if (ACPP_BaseDrone* Drone = Cast<ACPP_BaseDrone>(GetOwner()))
		{
			if (ACPP_DroneController* Controller = Cast<ACPP_DroneController>(GetOwner()->GetInstigatorController()))
			{
				Controller->SetPlayerEnabledState(false);
			}

			bDie = true;
			
			Drone->GetFrameDrone()->SetSimulatePhysics(true);
			
			FTimerHandle TimerHandle;
			float DelayInSeconds = 5.0f;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, &TimerHandle]() {

				if (UWorld* const World = GetWorld())
					{
						UGameplayStatics::OpenLevel(World, FName("TestLevel"));
						GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
					}
				}, DelayInSeconds, false);
			return;
		}
		
		GetOwner()->Destroy();		
	}

}

