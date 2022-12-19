// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SIHUD.h"

#include "Blueprint/UserWidget.h"
#include "Components/HealthComponent.h"
#include "Components/ScoreComponent.h"
#include "UI/SIEndGameWidget.h"
#include "UI/SIPlayerDataWidget.h"

void ASIHUD::EndGame(const float FinalScore)
{
	if (SIPlayerDataWidget)
	{
		SIPlayerDataWidget->RemoveFromParent();
	}
	if (SIEndGameWidgetClass)
	{
		SIEndGameWidget = CreateWidget<USIEndGameWidget>(GetOwningPlayerController(), SIEndGameWidgetClass);
		SIEndGameWidget->Initialize();
		SIEndGameWidget->Refresh(FinalScore);
		SIEndGameWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ASIHUD::EndGame(const float): SIEndGameWidgetClass is not valid."));
	}
}

void ASIHUD::BeginPlay()
{
	Super::BeginPlay();

	const AActor* OwningPawn = GetOwningPawn();
	if (!OwningPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASIHUD::BeginPlay(): OwningPawn is not valid."));
		return;
	}
	if (!SIPlayerDataWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASIHUD::BeginPlay(): SIPlayerDataWidgetClass is not valid."));
		return;
	}
	
	SIPlayerDataWidget = CreateWidget<USIPlayerDataWidget>(GetOwningPlayerController(), SIPlayerDataWidgetClass);
	SIPlayerDataWidget->AddToViewport();
	
	if (UHealthComponent* OwningPawnHealthComponent = Cast<UHealthComponent>(OwningPawn->GetComponentByClass(UHealthComponent::StaticClass())))
	{
		OwningPawnHealthComponent->OnCurrentHealthChanged.AddDynamic(this, &ASIHUD::UpdateHealth);
		SIPlayerDataWidget->RefreshHealth(OwningPawnHealthComponent->GetCurrentHealth());
	}
	if (UScoreComponent* OwningPawnScoreComponent = Cast<UScoreComponent>(OwningPawn->GetComponentByClass(UScoreComponent::StaticClass())))
	{
		OwningPawnScoreComponent->OnScoreChanged.AddDynamic(this, &ASIHUD::UpdateScore);
		SIPlayerDataWidget->RefreshScore(OwningPawnScoreComponent->GetScore());
	}
}

void ASIHUD::UpdateHealth(const float NewHealth)
{
	if (SIPlayerDataWidget)
	{
		SIPlayerDataWidget->RefreshHealth(NewHealth);
	}
}

void ASIHUD::UpdateScore(const float NewScore)
{
	if (SIPlayerDataWidget)
	{
		SIPlayerDataWidget->RefreshScore(NewScore);
	}
}