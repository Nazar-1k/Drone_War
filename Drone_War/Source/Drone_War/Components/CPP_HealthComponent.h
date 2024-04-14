// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONE_WAR_API UCPP_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChangedDelegate;

public:	

	// Sets default values for this component's properties
	UCPP_HealthComponent();

public:
	
	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE bool IsDie() { return bDie; }

public:
	
	void AddHealh(float AddedHEalth);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Health Component")
	float MaxHealth = 100.0f;

	float CurrentHealth;

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	bool bDie = false;
		
};
