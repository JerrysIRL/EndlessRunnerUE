// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHudWidget.h"
#include "RunnerGameMode.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UGameHudWidget::InitializeHud(ARunnerGameMode* GameMode)
{
	if(GameMode)
	{
		Score->SetText(FText::AsNumber(0));
		GameMode->OnScoreChange.AddDynamic(this, &UGameHudWidget::SetScoreCount);
		GameMode->OnPlayerHit.AddDynamic(this, &UGameHudWidget::SetLifeValue);
	}
}

void UGameHudWidget::SetScoreCount(float Value)
{
	Score->SetText(FText::AsNumber(FMath::RoundToInt(Value)));
}

void UGameHudWidget::SetLifeValue(float Lifes)
{
	float HealthProcent = Lifes / 3;
	UE_LOG(LogTemp, Warning, TEXT("Healthprocent: %f"), HealthProcent);
	HealthImage->SetPercent(HealthProcent);
}
