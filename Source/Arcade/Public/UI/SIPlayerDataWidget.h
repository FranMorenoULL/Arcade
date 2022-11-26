// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SIPlayerDataWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class ARCADE_API USIPlayerDataWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* ScoreValueTextBlock;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* HealthIcon1;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* HealthIcon2;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* HealthIcon3;

public:
	void RefreshHealth(const float NewHealth);
	void RefreshScore(const float NewScore);
};
