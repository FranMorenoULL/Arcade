// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SIPlayerDataWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void USIPlayerDataWidget::RefreshHealth(const float NewHealth)
{
	if (HealthIcon1)
	{
		HealthIcon1->SetVisibility(NewHealth >= 1.f ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
	if (HealthIcon2)
	{
		HealthIcon2->SetVisibility(NewHealth >= 2.f ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
	if (HealthIcon3)
	{
		HealthIcon3->SetVisibility(NewHealth >= 3.f ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void USIPlayerDataWidget::RefreshScore(const float NewScore)
{
	if (ScoreValueTextBlock)
	{
		ScoreValueTextBlock->SetText(FText::AsNumber(FMath::TruncToInt(NewScore)));
	}
}