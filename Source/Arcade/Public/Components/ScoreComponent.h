// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, const float, NewScore);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnScoreChanged OnScoreChanged;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ScoreValue = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ScoreConceded = 100.f;
	
public:	
	UScoreComponent();

	float GetScore() const;
	float GetScoreConceded() const;
	void AddScore(const float ScoreToAdd);
		
};
