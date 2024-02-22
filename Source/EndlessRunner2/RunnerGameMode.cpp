// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGameMode.h"
#include "MovingPlatform.h"

void ARunnerGameMode::BeginPlay()
{
	Super::BeginPlay();
	auto initialPlatform = SpawnPlatform(false);
	LanePositions = {initialPlatform->LeftLane.Y, initialPlatform->CenterLane.Y, initialPlatform->RightLane.Y};

	for (int i = 0; i < InitialPlatformNum - 1; i++)
	{
		SpawnPlatform(true);
	}
}

AMovingPlatform* ARunnerGameMode::SpawnPlatform(bool SpawnObstacles)
{
	const auto Platform = GetWorld()->SpawnActor<AMovingPlatform>(PlatformBP, NextSpawnPosition, FRotator::ZeroRotator);
	NextSpawnPosition = Platform->GetSpawnPosition();
	if (SpawnObstacles)
	{
		//spawn obstacles.
	}
	return Platform;
}
