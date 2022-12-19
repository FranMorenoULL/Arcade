// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawner.generated.h"

class UBoxComponent;

UCLASS()
class ARCADE_API AActorSpawner : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ActorSpawnRate = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ActorsToSpawn = 3;
	
protected:
	FTimerHandle ActorSpawnTimerHandle;

public:
	AActorSpawner();
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnSpawn();
};
