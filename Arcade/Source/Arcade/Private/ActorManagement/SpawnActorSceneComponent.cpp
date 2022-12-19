// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorManagement/SpawnActorSceneComponent.h"

USpawnActorSceneComponent::USpawnActorSceneComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TSubclassOf<AActor> USpawnActorSceneComponent::GetActorToSpawn() const
{
	return ActorToSpawn;
}