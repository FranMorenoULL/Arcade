// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/SIPawn.h"

#include "Bullet.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/HealthComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASIPawn::ASIPawn()
{
	PrimaryActorTick.bCanEverTick = false;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	SetRootComponent(BoxCollision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(BoxCollision);
	
	Health = CreateDefaultSubobject<UHealthComponent>("Health");
	Health->OnDie.AddDynamic(this, &ASIPawn::Die);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
	
	Score = CreateDefaultSubobject<UScoreComponent>("Score");
}

void ASIPawn::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASIPawn::OnCollisionBeginOverlap);
}

void ASIPawn::MoveForward(float Value)
{
	if (-0.01f < Value && Value < 0.01f)
	{
		return;
	}
	Movement->AddInputVector(Value * GetActorForwardVector());
}

void ASIPawn::MoveRight(float Value)
{
	if (-0.01f < Value && Value < 0.01f)
	{
		return;
	}
	Movement->AddInputVector(Value * GetActorRightVector());
}

void ASIPawn::StartFire()
{
	bWantsToFire = true;
	if (!bCanFire)
	{
		return;
	}
	bCanFire = false;
	
	UWorld* World = GetWorld();
	if (!World || !BulletClass)
	{
		return;
	}
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Owner = ActorSpawnParameters.Instigator = this;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (const ABullet* Bullet = World->SpawnActor<ABullet>(BulletClass, GetActorLocation(), GetActorRotation(), ActorSpawnParameters))
	{
		if (FireSW)
		{
			UGameplayStatics::PlaySound2D(this, FireSW);
		}
		Bullet->Fire(BulletSpeed);
	}

	World->GetTimerManager().SetTimer(ResetFireTimerHandle, this, &ASIPawn::ResetFire, FireRate);
}

void ASIPawn::StopFire()
{
	bWantsToFire = false;
}

void ASIPawn::ResetFire()
{
	bCanFire = true;
	if (bWantsToFire)
	{
		StartFire();
	}
}

void ASIPawn::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag(FName("Tangible")))
	{
		return;
	}
	Health->TakeDamage(1.f);
}

void ASIPawn::Die()
{
	if (ExplosionNS)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionNS, GetActorLocation());
	}
	if (ExplosionSW)
	{
		UGameplayStatics::PlaySound2D(this, ExplosionSW);
	}
}