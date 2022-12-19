// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Components/BoxComponent.h"
#include "Components/HealthComponent.h"
#include "Components/ScoreComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Box);
	
	Health = CreateDefaultSubobject<UHealthComponent>("Health");
	Health->OnDie.AddDynamic(this, &ABullet::Die);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->SetUpdatedComponent(Box);
	Movement->bRotationFollowsVelocity = true;
	Movement->bShouldBounce = false;
	Movement->ProjectileGravityScale = 0.0f;
}

void ABullet::Fire(const float Speed) const
{
	Movement->InitialSpeed = Speed;
	Movement->MaxSpeed = Speed;
	Movement->Velocity = Speed * GetActorForwardVector();
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnCollisionBeginOverlap);
}

void ABullet::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag(FName("Tangible")))
	{
		return;
	}
	if (const AActor* SelfInstigator = GetInstigator())
	{
		const UScoreComponent* OtherActorScoreComponent = Cast<UScoreComponent>(OtherActor->GetComponentByClass(UScoreComponent::StaticClass()));
		UScoreComponent* SelfInstigatorScoreComponent = Cast<UScoreComponent>(SelfInstigator->GetComponentByClass(UScoreComponent::StaticClass()));
		if (OtherActorScoreComponent && SelfInstigatorScoreComponent)
		{
			SelfInstigatorScoreComponent->AddScore(OtherActorScoreComponent->GetScoreConceded());
		}
	}
	Health->TakeDamage(1.f);
}

void ABullet::Die()
{
	if (UWorld* World = GetWorld())
	{
		World->DestroyActor(this);
		if (ExplosionNS)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionNS, GetActorLocation());
		}
		if (ExplosionSW)
		{
			UGameplayStatics::PlaySound2D(this, ExplosionSW);
		}
	}
}