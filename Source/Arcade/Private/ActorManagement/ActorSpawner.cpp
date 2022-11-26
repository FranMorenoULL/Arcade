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
	const int NEnemiesToSpawn = FMath::RandRange(1, SpawnActorSceneComponents.Num());
	for (int i = 0; i < NEnemiesToSpawn; ++i)
	{
		if (const TSubclassOf<AActor> ActorToSpawn = SpawnActorSceneComponents[i]->GetActorToSpawn())
		{
			World->SpawnActor(ActorToSpawn, &SpawnActorSceneComponents[i]->GetComponentTransform());
		}
	}
}
