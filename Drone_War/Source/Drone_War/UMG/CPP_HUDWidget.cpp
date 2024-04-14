// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_HUDWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "../Pawns/Drone/CPP_BaseDrone.h"
#include "../Components/CPP_HealthComponent.h"

void UCPP_HUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

    if (ACPP_BaseDrone* PlayerPawn = Cast<ACPP_BaseDrone>(GetOwningPlayerPawn()))
    {
        HealthComponent = PlayerPawn->GetHealthComponent();
        if (HealthComponent)
        {
            // Set Current Persent for progres bar
            OnChangeHealth(HealthComponent->GetCurrentHealth());
            
            HealthComponent->OnHealthChangedDelegate.AddDynamic(this, &UCPP_HUDWidget::OnChangeHealth);
        }

        OnShoot(PlayerPawn->GetCountAmmo());
        PlayerPawn->OnShootDelegate.AddDynamic(this, &UCPP_HUDWidget::OnShoot);
    }
}

void UCPP_HUDWidget::OnChangeHealth(float Health)
{
    HealthProgressBar->SetPercent(GetHealthPercent(Health));

    if (GetHealthPercent(Health) <= LowHpPersent)
    {
        HealthProgressBar->SetFillColorAndOpacity(LowHPBorderColor);
    }
    else
    {
        HealthProgressBar->SetFillColorAndOpacity(NormalHPBorderColor);
    }
}

void UCPP_HUDWidget::OnShoot(int32 CountAmmo)
{
    AvailableWeaponAmmoText->SetText(FText::AsNumber(CountAmmo));
}

float UCPP_HUDWidget::GetHealthPercent(float Health)
{
    return Health / HealthComponent->GetMaxHealth();
}
