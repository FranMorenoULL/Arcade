// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

void UHealthComponent::TakeDamage(const float DmgAmount)
{
	if (CurrentHealth <= 0.f)
	{
		return;
	}
	
	CurrentHealth = FMath::Max(CurrentHealth - DmgAmount, 0.f);
	
	OnCurrentHealthChanged.Broadcast(CurrentHealth);
	
	if (CurrentHealth <= 0.f)
	{
		OnDie.Broadcast();
	}
}