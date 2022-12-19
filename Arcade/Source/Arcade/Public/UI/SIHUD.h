// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SIHUD.generated.h"

class USIEndGameWidget;
class USIPlayerDataWidget;

UCLASS()
class ARCADE_API ASIHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USIPlayerDataWidget> SIPlayerDataWidgetClass;
	
	UPROPERTY(VisibleAnywhere)
	USIPlayerDataWidget* SIPlayerDataWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<USIEndGameWidget> SIEndGameWidgetClass;
	
	UPROPERTY(VisibleAnywhere)
	USIEndGameWidget* SIEndGameWidget;

public:
	void EndGame(const float FinalScore);
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateHealth(const float NewHealth);
	UFUNCTION()
	void UpdateScore(const float NewScore);
};
