// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "../Pawns/CPP_BasePawn.h"

// Sets default values
ACPP_Projectile::ACPP_Projectile()
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	Collision->SetupAttachment(ProjectileMesh);

	ProjectileMoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Move Component"));
}

// Called when the game starts or when spawned
void ACPP_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ACPP_Projectile::OnHit);
	// Time to destroy
	SetLifeSpan(TimeToLive);
}

void ACPP_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ACPP_BasePawn* CharacterToDamage = Cast<ACPP_BasePawn>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(CharacterToDamage, Damage, GetInstigatorController(), this, nullptr);
	}

	Destroy();
}


