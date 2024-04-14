// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseDrone.h"
#include "CPP_AdvancedDrone.generated.h"

class UBoxComponent;

struct FInputActionValue;
class UInputMappingContext;

class UCPP_EngineComponent;

UCLASS()
class DRONE_WAR_API ACPP_AdvancedDrone : public ACPP_BaseDrone
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_AdvancedDrone();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	/** Called for movement input */
	void Move(const FInputActionValue& Value) override;

	/** Called for End Move input */
	void EndMove(const FInputActionValue& Value) override;

	/** Called for movement input */
	void MoveUp(const FInputActionValue& Value) override;

	void MoveYaw(const FInputActionValue& Value) override;
	void EndMoveYaw(const FInputActionValue& Value) override;

public:

	FORCEINLINE UStaticMeshComponent* GetFrameDrone() { return FrameDrone; };

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;

	/** Front Left Engine Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Engines", meta = (AllowPrivateAccess = "true"))
	UCPP_EngineComponent* FrontLeftEngine;

	/** Front Right Engine Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Engines", meta = (AllowPrivateAccess = "true"))
	UCPP_EngineComponent* FrontRightEngine;

	/** Back Left Engine Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Engines", meta = (AllowPrivateAccess = "true"))
	UCPP_EngineComponent* BackLeftEngine;

	/** Back Right Engine Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Engines", meta = (AllowPrivateAccess = "true"))
	UCPP_EngineComponent* BackRightEngine;

	/** Array for calculation */
	TArray<UCPP_EngineComponent*> Engines;

private:
	
	void AltitudeStabilization(float DeltaTime);

	void Pitch(float Force,float DeltaTime);
	void Roll(float Force, float DeltaTime);
	void Yaw(float Force, float DeltaTime);

	void PitchStabilization(float DeltaTime);
	void RollStabilization(float DeltaTime);
	void YawStabilization(float DeltaTime);

private:

private:

	bool IsPitchMove = false;
	bool IsRollMove = false;
	bool IsYawMove = false;
	
	/** Height that the copter will try to keep */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float DesiredAltitude;

	/** Altitude Integral */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float AltitudeIntegral;

	/** Altitude Error Prior */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float AltitudeErrorPrior;

	/** Altitude Control Error Prior */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float AltitudeStabilisationForceMultiplier = 2000.f;

	/** Manual Throttle Force Multiplier */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float ManualThrottleForceMultiplier = 150.f;

	/** Pitch Roll Multiplier */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float PitchRollMultiplier = 100000.f;

	/** YawMultiplier */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float YawMultiplier = 200000.f;

private:

	/** Pitch ErrorPrior */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float PitchErrorPrior;

	/** Pitch Integral */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float PitchIntegral;

	/** Manual Throttle Force Multiplier */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float PitchStabilizationMultiplier = 100000.f;

	/** Roll ErrorPrior */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float RollErrorPrior;

	/** Pitch Integral */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float RollIntegral;

	/** Roll Stabilization Multiplier */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float RollStabilizationMultiplier = 100000.f;


	/** Roll ErrorPrior */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float YawErrorPrior;

	/** Pitch Integral */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float YawIntegral;

	/** Roll Stabilization Multiplier */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting for fly", meta = (AllowPrivateAccess = "true"))
	float YawStabilizationMultiplier = 100000.f;


private:

	/** Function is used to calculate the control signal to control the drone using the PID algorithm. */
	UFUNCTION(BlueprintCallable, Category = "PID")
	float PIDCalculation(float CurrentValue, float DesiredValue, float P, float I, float D, float Bias, float DeltaTime, float& Integral, float& ErrorPrior);
};
