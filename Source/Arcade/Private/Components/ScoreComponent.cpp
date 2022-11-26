// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ScoreComponent.h"

UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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