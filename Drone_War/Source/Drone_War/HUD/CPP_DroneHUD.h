// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CPP_DroneHUD.generated.h"


class UCPP_HUDWidget;

UCLASS()
class DRONE_WAR_API ACPP_DroneHUD : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "WidgetClass")
	TSubclassOf<UCPP_HUDWidget> HUDWidgetClass;
	TObjectPtr<UCPP_HUDWidget> HUDWidgetInstance;
};
