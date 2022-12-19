// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BillboardComponent.h"
#include "SpawnActorSceneComponent.generated.h"

UCLASS(ClassGroup = (Spawner), meta = (BlueprintSpawnableComponent))
class ARCADE_API USpawnActorSceneComponent : public UBillboardComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorToSpawn;

public:
	USpawnActorSceneComponent();

	TSubclassOf<AActor> GetActorToSpawn() const;
};
