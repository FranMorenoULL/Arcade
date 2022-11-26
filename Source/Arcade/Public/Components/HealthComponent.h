// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentHealthChanged, const float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnCurrentHealthChanged OnCurrentHealthChanged;
	FOnDie OnDie;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentHealth;
	
public:
	UHealthComponent();

	float GetCurrentHealth() const;
	void TakeDamage(const float DmgAmount);
	
};
