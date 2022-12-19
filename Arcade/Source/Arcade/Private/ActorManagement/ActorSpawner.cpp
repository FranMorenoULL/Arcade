// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorManagement/ActorSpawner.h"

#include "ActorManagement/SpawnActorSceneComponent.h"
#include "Components/BoxComponent.h"

AActorSpawner::AActorSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(ActorSpawnTimerHandle, this, &AActorSpawner::OnSpawn, ActorSpawnRate, true);
	}
}

void AActorSpawner::OnSpawn()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	TArray<USpawnActorSceneComponent*> SpawnActorSceneComponents;
	GetComponents<USpawnActorSceneComponent>(SpawnActorSceneComponents, false);
	if (SpawnActorSceneComponents.IsEmpty())
	{
		return;
	}
	
	SpawnActorSceneComponents.Sort([](const USpawnActorSceneComponent&, const USpawnActorSceneComponent&)
	{
		return FMath::RandRange(0,1) == 1;
	});
	for (int i = 0; i < ActorsToSpawn; ++i)
	{
		if (const TSubclassOf<AActor> ActorToSpawn = SpawnActorSceneComponents[i]->GetActorToSpawn())
		{
			const FVector SpawnLocation = SpawnActorSceneComponents[i]->GetComponentLocation() + FMath::RandRange(-10.f,10.f) * FVector(0.f, 0.f, 1.f);
			const FRotator SpawnRotation = SpawnActorSceneComponents[i]->GetComponentRotation();
			World->SpawnActor(ActorToSpawn, &SpawnLocation, &SpawnRotation);
		}
	}
}
