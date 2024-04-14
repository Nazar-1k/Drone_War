// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DroneHUD.h"

#include "../UMG/CPP_HUDWidget.h"

void ACPP_DroneHUD::BeginPlay()
{
	Super::BeginPlay();

    if (HUDWidgetClass)
    {
        HUDWidgetInstance = CreateWidget<UCPP_HUDWidget>(GetWorld(), HUDWidgetClass);
        if (HUDWidgetInstance)
        {
            HUDWidgetInstance->AddToViewport();
        }
    }
}
