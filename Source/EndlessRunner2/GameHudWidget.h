// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHudWidget.generated.h"


class ARunnerGameMode;

UCLASS()
class ENDLESSRUNNER2_API UGameHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* Score;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* HealthImage;

	UFUNCTION(BlueprintCallable)
	void InitializeHud(ARunnerGameMode* GameMode);

	UFUNCTION(BlueprintCallable)
	void SetScoreCount(float Value);

	UFUNCTION(BlueprintCallable)
	void SetLifeValue(float Lifes);
};
