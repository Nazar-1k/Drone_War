// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_HUDWidget.generated.h"

class UProgressBar;
class UTextBlock;

class UCPP_HealthComponent;

UCLASS()
class DRONE_WAR_API UCPP_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* AvailableWeaponAmmoText;

private:

	UFUNCTION()
	void OnChangeHealth(float Health);

	UFUNCTION()
	void OnShoot(int32 CountAmmo);

	float GetHealthPercent(float Health);

private:

	UCPP_HealthComponent* HealthComponent;
	
	/** Health point persent when progres bar stay red */
	UPROPERTY(EditAnywhere, Category = "Settings|HP")
	float LowHpPersent = 0.3;

	UPROPERTY(EditAnywhere, Category = "Settings|Color")
	FLinearColor LowHPBorderColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, Category = "Settings|Color")
	FLinearColor NormalHPBorderColor = FLinearColor::Green;

};
