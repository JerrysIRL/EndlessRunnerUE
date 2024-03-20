// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHudWidget.h"

#include "RunnerGameMode.h"
#include "Components/TextBlock.h"

void UGameHudWidget::InitializeHud(ARunnerGameMode* GameMode)
{
	if(GameMode)
	{
		Score->SetText(FText::AsNumber(0));
		GameMode->OnScoreChange.AddDynamic(this, &UGameHudWidget::SetScoreCount);
	}
}

void UGameHudWidget::SetScoreCount(float Value)
{
	Score->SetText(FText::AsNumber(Value));
}
