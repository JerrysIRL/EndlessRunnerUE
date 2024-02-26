// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGameMode.h"
#include "MovingPlatform.h"
#include "Components/ArrowComponent.h"

void ARunnerGameMode::BeginPlay()
{
	Super::BeginPlay();
	const auto initialPlatform = GetWorld()->SpawnActor<AMovingPlatform>(PlatformBP, FVector::Zero(), FRotator::ZeroRotator);
	NextSpawnPosition = initialPlatform->GetSpawnPosition();
	LanePositions = {
		initialPlatform->LeftLane->GetComponentLocation().Y,
		initialPlatform->CenterLane->GetComponentLocation().Y,
		initialPlatform->RightLane->GetComponentLocation().Y
	};
	bool spawnObstacles = false;
	for (int i = 0; i < InitialPlatformNum - 1; i++)
	{
		SpawnPlatform(spawnObstacles);
		spawnObstacles = !spawnObstacles;
	}
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
