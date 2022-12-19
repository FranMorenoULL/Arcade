// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SIEndGameWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class ARCADE_API USIEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* ScoreValueTextBlock;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* RestartGameButton;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* ExitGameButton;

public:
	virtual bool Initialize() override;
	void Refresh(const float FinalScore) const;

protected:
	UFUNCTION()
	void OnRestartGameClicked();
};
