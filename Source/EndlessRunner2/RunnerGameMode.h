// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPlatform.h"
#include "GameFramework/GameModeBase.h"
#include "RunnerGameMode.generated.h"

class UGameHudWidget;
class AObstacle;
class AMovingPlatform;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinCollected, float, CoinCollect);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerHit, float, PlayerHit);

UCLASS()
class ENDLESSRUNNER2_API ARunnerGameMode : public AGameModeBase
{
public:
	ARunnerGameMode();

private:
	GENERATED_BODY()

protected:
	UPROPERTY()
	FTimerHandle SpeedTimerHandle;

	UPROPERTY(EditAnywhere)
	int InitialPlatformNum = 10;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMovingPlatform> PlatformBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameHudWidget> HudWidgetBP;

	UPROPERTY(VisibleInstanceOnly)
	UGameHudWidget* HudWidget;

	AMovingPlatform* SpawnPlatform(const bool SpawnObstacles);

	virtual void BeginPlay() override;

public:
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCoinCollected OnScoreChange;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPlayerHit OnPlayerHit;

	UPROPERTY()
	float Score = 0;

	UPROPERTY()
	bool IsObstacleWave = false;

	UPROPERTY()
	TArray<double> LanePositions;

	UFUNCTION(BlueprintCallable)
	void AddScore(float Value);

	UPROPERTY(EditDefaultsOnly)
	float StartSpeed = 500;
	
	UPROPERTY(EditDefaultsOnly)
	float SpeedIncrease = 10;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxSpeed = 1000;

	UPROPERTY(EditDefaultsOnly)
	float SpeedIncreaseTime = 3;

	USceneComponent* GetNextSpawnPoint() const { return NextSpawnPosition; }

	float GetSpeed() const { return CurrentPlatformSpeed; }

	void SetNextSpawnPoint(USceneComponent* Value) { NextSpawnPosition = Value; }

private:
	
	UPROPERTY()
	float CurrentPlatformSpeed = 500;
	
	UFUNCTION()
	void AddSpeed();

	UPROPERTY()
	USceneComponent* NextSpawnPosition;

	virtual void Tick(float DeltaTime) override;
};
