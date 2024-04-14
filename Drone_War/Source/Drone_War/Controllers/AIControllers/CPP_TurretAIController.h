#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h" 
#include "Perception/AISenseConfig_Sight.h" 

#include "CPP_TurretAIController.generated.h"

UCLASS()
class DRONE_WAR_API ACPP_TurretAIController : public AAIController
{
    GENERATED_BODY()

public:
    ACPP_TurretAIController();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnPerceptionFollow(AActor* Actor, FAIStimulus Stimulus);

    void OnPossess(APawn* InPawn) override;

private:
    UPROPERTY(EditAnywhere)
    class UBehaviorTree* AIBahaviorTree;

    UPROPERTY(VisibleAnywhere, Category = "Perception")
    UAIPerceptionComponent* PerceptionFollowComponent;
    UAISenseConfig_Sight* SightFollow;

    UPROPERTY(EditDefaultsOnly, Category = "Perception|Setting")
    float SightRadius = 1000.f;

    UPROPERTY(EditDefaultsOnly, Category = "Perception|Setting")
    float LoseSightRadius = 2000.f;

    UPROPERTY(EditDefaultsOnly, Category = "Perception|Setting")
    float PeripheralVisionAngleDegrees = 180.f;
};
