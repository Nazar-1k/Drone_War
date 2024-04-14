// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AdvancedDrone.h"

#include "Kismet/GameplayStatics.h"

#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"

#include "InputActionValue.h"

#include "../../Components/CPP_HealthComponent.h"
#include "../../Components/CPP_EngineComponent.h"
#include "../../Projectile/CPP_Projectile.h"

ACPP_AdvancedDrone::ACPP_AdvancedDrone()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetSimulatePhysics(true);
	Box->SetMassOverrideInKg(NAME_None, 1.0f);
	Box->SetCollisionProfileName(TEXT("BlockAll_Dynamic"));
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	RootComponent = Box;

	// Attachment FrameDrone
	FrameDrone->SetupAttachment(Box);

	// Engines
	FrontLeftEngine = CreateDefaultSubobject<UCPP_EngineComponent>(TEXT("Front Left Engine Component"));
	FrontLeftEngine->SetupAttachment(FrontLeftPropeler);
	FrontLeftEngine->SetClockwise(true);

	FrontRightEngine = CreateDefaultSubobject<UCPP_EngineComponent>(TEXT("Front Right Engine Component"));
	FrontRightEngine->SetupAttachment(FrontRightPropeler);
	FrontRightEngine->SetClockwise(true);

	BackLeftEngine = CreateDefaultSubobject<UCPP_EngineComponent>(TEXT("Back Left Engine Component"));
	BackLeftEngine->SetupAttachment(BackLeftPropeler);
	BackLeftEngine->SetClockwise(false);
	
	BackRightEngine = CreateDefaultSubobject<UCPP_EngineComponent>(TEXT("Back Right Engine Component"));
	BackRightEngine->SetupAttachment(BackRightPropeler);
	BackRightEngine->SetClockwise(false);

	// Add Engines to Array
	Engines.Add(FrontLeftEngine);
	Engines.Add(FrontRightEngine);
	Engines.Add(BackLeftEngine);
	Engines.Add(BackRightEngine);

	PrimaryActorTick.bCanEverTick = true;
}

void ACPP_AdvancedDrone::BeginPlay()
{	
	Super::BeginPlay();

	// Set start Amplitude Desired
	DesiredAltitude = GetActorLocation().Z;
}

void ACPP_AdvancedDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AltitudeStabilization(DeltaTime);

	if (!IsPitchMove)
	{
		PitchStabilization(DeltaTime);
	}

	if (!IsRollMove)
	{
		RollStabilization(DeltaTime);
	}
	if (!IsYawMove)
	{
		YawStabilization(DeltaTime);
	}
}

void ACPP_AdvancedDrone::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// Pitch
	float MovmentPitch = MovementVector.Y;
	float PitchForce = PitchRollMultiplier * MovmentPitch;
	
	if (PitchForce == 0)
	{
		IsPitchMove = false;
	}
	else
	{
		IsPitchMove = true;
		Pitch(PitchForce, UGameplayStatics::GetWorldDeltaSeconds(this));
	}

	// Roll
	float MovmentRoll = MovementVector.X;
	float RollForce = PitchRollMultiplier * MovmentRoll;

	if (RollForce == 0)
	{
		IsRollMove = false;
	}
	else
	{	
		Roll(RollForce, UGameplayStatics::GetWorldDeltaSeconds(this));
		IsRollMove = true;
	}


}

void ACPP_AdvancedDrone::EndMove(const FInputActionValue& Value)
{
	IsPitchMove = false;
	IsRollMove = false;
}

void ACPP_AdvancedDrone::MoveUp(const FInputActionValue& Value)
{
	float Movement = Value.Get<float>();

	DesiredAltitude += ManualThrottleForceMultiplier * Movement * UGameplayStatics::GetWorldDeltaSeconds(this);
}

void ACPP_AdvancedDrone::MoveYaw(const FInputActionValue& Value)
{
	float MovmentYaw = Value.Get<float>();

	float YawForce = YawMultiplier * MovmentYaw;

	if (YawForce == 0)
	{
		IsYawMove = false;
	}
	else
	{
		Yaw(YawForce, UGameplayStatics::GetWorldDeltaSeconds(this));
		IsYawMove = true;
	}
}

void ACPP_AdvancedDrone::EndMoveYaw(const FInputActionValue& Value)
{
	IsYawMove = false;
}

void ACPP_AdvancedDrone::AltitudeStabilization(float DeltaTime)
{
	float DroneZLocation = GetActorLocation().Z;

	float OutForce = PIDCalculation(DroneZLocation, DesiredAltitude, 0.2f, 0.005f, 0.1f, 0, DeltaTime, AltitudeIntegral, AltitudeErrorPrior);

	float AltitudeStabilisationForce = AltitudeStabilisationForceMultiplier * OutForce * -1;

	for (UCPP_EngineComponent* Engine : Engines)
	{
		Engine->AddUpForce(AltitudeStabilisationForce);
	}

}

void ACPP_AdvancedDrone::Pitch(float Force, float DeltaTime)
{
	float PitchForce = Force * DeltaTime;

	if (PitchForce != 0)
	{
		FrontLeftEngine->AddUpForce(-PitchForce);
		FrontRightEngine->AddUpForce(-PitchForce);

		BackLeftEngine->AddUpForce(PitchForce);
		BackRightEngine->AddUpForce(PitchForce);
	}
}

void ACPP_AdvancedDrone::Roll(float Force, float DeltaTime)
{
	float RollForce = Force * DeltaTime;
	
	if(RollForce != 0)
	{
		FrontLeftEngine->AddUpForce(-RollForce);
		BackLeftEngine->AddUpForce(-RollForce);

		FrontRightEngine->AddUpForce(RollForce);
		BackRightEngine->AddUpForce(RollForce);
	}	
}

void ACPP_AdvancedDrone::Yaw(float Force, float DeltaTime)
{
	float YawForce = Force * DeltaTime;
	
	if (YawForce != 0)
	{
		for (UCPP_EngineComponent* Engine : Engines)
		{
			Engine->AddYawForce(YawForce);
		}
	}
}

void ACPP_AdvancedDrone::PitchStabilization(float DeltaTime)
{
	float BoxPitch =  Box->GetComponentRotation().Pitch;

	float OutForce = PIDCalculation(BoxPitch, 0.f, 0.4f, 0.0005f, 0.002f, 0, DeltaTime, PitchIntegral, PitchErrorPrior);

	float StabilizationForce = OutForce * PitchStabilizationMultiplier;

	Pitch(StabilizationForce, DeltaTime);
	
}

void ACPP_AdvancedDrone::RollStabilization(float DeltaTime)
{
	float BoxRoll = Box->GetComponentRotation().Roll;

	float OutForce = PIDCalculation(BoxRoll, 0.f, 0.002f, 0.0005f, 0.002f, 0, DeltaTime, RollIntegral, RollErrorPrior);

	float StabilizationForce = OutForce * RollStabilizationMultiplier;

	Pitch(-StabilizationForce, DeltaTime);

}

void ACPP_AdvancedDrone::YawStabilization(float DeltaTime)
{
	float VelocityInDegreesZ = Box->GetPhysicsAngularVelocityInDegrees().Z;

	float OutForce = PIDCalculation(VelocityInDegreesZ, 0.f, 0.5f, 0.005f, 0.003f, 0, DeltaTime, YawIntegral, YawErrorPrior);

	float StabilizationForce = OutForce * YawStabilizationMultiplier;

	Pitch(-StabilizationForce, DeltaTime);

}

float ACPP_AdvancedDrone::PIDCalculation(float CurrentValue, float DesiredValue, float P, float I, float D, float Bias, float DeltaTime, float& Integral, float& ErrorPrior)
{
	// Get the previous integral and error values
	float pIntegral = Integral;           // Previous integral value
	float pErrorPrior = ErrorPrior;       // Previous error

	// Calculate the current error
	float pError = CurrentValue - DesiredValue;

	// Calculate the derivative
	float pDerivative;

	// Calculate the integral
	pIntegral += pErrorPrior * DeltaTime;

	// Calculate the derivative
	pDerivative = (pError - pErrorPrior) / DeltaTime;

	// Update the integral and error values for use on the next step
	Integral = pIntegral;       // Updated integral value
	ErrorPrior = pError;        // Updated error

	// Calculate the output force using the PID algorithm
	float OutForce = (P * pError) + (I * pIntegral) + (D * pDerivative) + Bias;

	// Return the output force
	return OutForce;
}
