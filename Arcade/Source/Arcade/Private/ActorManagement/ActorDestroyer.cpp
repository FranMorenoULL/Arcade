// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorManagement/ActorDestroyer.h"

#include "Components/BoxComponent.h"

AActorDestroyer::AActorDestroyer()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	SetRootComponent(BoxCollision);
}

void AActorDestroyer::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AActorDestroyer::OnCollisionBeginOverlap);
}

void AActorDestroyer::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UWorld* World = GetWorld())
	{
		World->DestroyActor(OtherActor);
	}
}
