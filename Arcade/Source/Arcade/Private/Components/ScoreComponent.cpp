// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ScoreComponent.h"

#include "Components/HealthComponent.h"

UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UScoreComponent::BeginPlay()
{
	if (PassiveScoreRate > 0.f)
	{
		if (const UWorld* World = GetWorld())
		{
			FTimerDelegate PassiveScoreDelegate;
			PassiveScoreDelegate.BindLambda([this]()
			{
				AddScore(PassiveScoreAmount);
			});
			World->GetTimerManager().SetTimer(PassiveScoreTimerHandle, PassiveScoreDelegate, PassiveScoreRate, true);
		}
		if (const AActor* Owner = GetOwner())
		{
			if (UHealthComponent* OwnerHealth = Cast<UHealthComponent>(Owner->GetComponentByClass(UHealthComponent::StaticClass())))
			{
				OwnerHealth->OnDie.AddDynamic(this, &UScoreComponent::StopPassiveScore);
			}
		}
	}
}

float UScoreComponent::GetScore() const
{
	return ScoreValue;
}

float UScoreComponent::GetScoreConceded() const
{
	return ScoreConceded;
}

void UScoreComponent::AddScore(const float ScoreToAdd)
{
	ScoreValue += ScoreToAdd;
	OnScoreChanged.Broadcast(ScoreValue);
}

void UScoreComponent::StopPassiveScore()
{
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(PassiveScoreTimerHandle);
		PassiveScoreTimerHandle.Invalidate();
	}
}