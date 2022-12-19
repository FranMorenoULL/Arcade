// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SIEndGameWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

bool USIEndGameWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	if (RestartGameButton)
	{
		RestartGameButton->OnClicked.AddDynamic(this, &USIEndGameWidget::OnRestartGameClicked);
	}
	return true;
}

void USIEndGameWidget::Refresh(const float FinalScore) const
{
	if (ScoreValueTextBlock)
	{
		ScoreValueTextBlock->SetText(FText::AsNumber(FMath::TruncToInt(FinalScore)));
	}
}

void USIEndGameWidget::OnRestartGameClicked()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}