// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGameMode.h"
#include "MovingPlatform.h"

void ARunnerGameMode::BeginPlay()
{
	Super::BeginPlay();
	auto testPlatform = SpawnPlatform();
	LanePositions = {testPlatform->LeftLane, testPlatform->CenterLane, testPlatform->RightLane};

	for (int i = 0; i < InitialPlatformNum-1; i++)
	{
		SpawnPlatform();
	}
}

AMovingPlatform* ARunnerGameMode::SpawnPlatform()
{
	const auto Platform = GetWorld()->SpawnActor<AMovingPlatform>(PlatformBP, NextSpawnPosition, FRotator::ZeroRotator);
	NextSpawnPosition = Platform->GetSpawnPosition();
	return Platform;
}
