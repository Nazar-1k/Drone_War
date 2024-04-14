// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BasePickUp.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

#include "../Pawns/CPP_BasePawn.h"

// Sets default values
ACPP_BasePickUp::ACPP_BasePickUp()
{
	// Create the static mesh component
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	RootComponent = NiagaraComponent;

	// Create the collection sphere
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->SetupAttachment(NiagaraComponent);
	CollectionSphere->SetSphereRadius(40.0f);

}

void ACPP_BasePickUp::BeginPlay()
{
	Super::BeginPlay();

	CollectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACPP_BasePickUp::CollectPickups);
}


void ACPP_BasePickUp::WasCollected(ACPP_BasePawn* Drone)
{
	NiagaraComponent->DestroyComponent();
	Destroy();
}

void ACPP_BasePickUp::CollectPickups(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACPP_BasePawn* Drone = Cast<ACPP_BasePawn>(OtherActor))
	{
		if (!Drone->IsLoose())
		{
			WasCollected(Drone);
		}
	}
}
