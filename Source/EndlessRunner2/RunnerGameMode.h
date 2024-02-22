// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPlatform.h"
#include "GameFramework/GameModeBase.h"
#include "RunnerGameMode.generated.h"

class AObstacle;
class AMovingPlatform;

UCLASS()
class ENDLESSRUNNER2_API ARunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMovingPlatform> PlatformBP;

	UPROPERTY(EditAnywhere)
	int InitialPlatformNum = 10;

	AMovingPlatform* SpawnPlatform(const bool SpawnObstacles);

	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<AObstacle*> Obstacles;

public:
	USceneComponent* GetNextSpawnPoint() const { return NextSpawnPosition; }

	void SetNextSpawnPoint(USceneComponent* Value) { NextSpawnPosition = Value; }

	UPROPERTY()
	TArray<double> LanePositions;

private:
	UPROPERTY()
	USceneComponent* NextSpawnPosition;
};
