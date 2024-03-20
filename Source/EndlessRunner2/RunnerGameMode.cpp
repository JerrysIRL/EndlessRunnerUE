// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGameMode.h"

#include "GameHudWidget.h"
#include "MovingPlatform.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ARunnerGameMode::ARunnerGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}


void ARunnerGameMode::BeginPlay()
{
	Super::BeginPlay();

	HudWidget = CreateWidget<UGameHudWidget>(GetWorld(), HudWidgetBP);
	check(HudWidget);
	HudWidget->InitializeHud(this);
	HudWidget->AddToViewport();

	CurrentPlatformSpeed = StartSpeed;
	GetWorld()->GetTimerManager().SetTimer(SpeedTimerHandle, this, &ARunnerGameMode::AddSpeed, SpeedIncreaseTime, true);
	
	const auto initialPlatform = GetWorld()->SpawnActor<AMovingPlatform>(PlatformBP, FVector::Zero(), FRotator::ZeroRotator);
	NextSpawnPosition = initialPlatform->GetSpawnPosition();
	LanePositions = {
		initialPlatform->LeftLane->GetComponentLocation().Y,
		initialPlatform->CenterLane->GetComponentLocation().Y,
		initialPlatform->RightLane->GetComponentLocation().Y
	};
	
	for (int i = 0; i < InitialPlatformNum - 1; i++)
	{
		SpawnPlatform(IsObstacleWave);
		IsObstacleWave = !IsObstacleWave;
	}
}

void ARunnerGameMode::AddSpeed()
{
	CurrentPlatformSpeed = FMath::Clamp(CurrentPlatformSpeed + SpeedIncrease, 0, MaxSpeed);
	UE_LOG(LogTemp, Warning, TEXT("Adding speed, current: %f"), CurrentPlatformSpeed);
}

void ARunnerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Score += DeltaTime;
	OnScoreChange.Broadcast(Score);
}

AMovingPlatform* ARunnerGameMode::SpawnPlatform(bool SpawnObstacles)
{
	const auto Platform = GetWorld()->SpawnActor<AMovingPlatform>(PlatformBP, NextSpawnPosition->GetComponentLocation(), FRotator::ZeroRotator);
	NextSpawnPosition = Platform->GetSpawnPosition();
	if (SpawnObstacles)
	{
		Platform->SpawnObstacleWave();
	}
	return Platform;
}

void ARunnerGameMode::AddScore(float Value)
{
	Score += Value;
	OnScoreChange.Broadcast(Score);
}
