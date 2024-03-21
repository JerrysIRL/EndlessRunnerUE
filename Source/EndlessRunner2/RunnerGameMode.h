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

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category= Platforms)
	int InitialPlatformNum = 10;

	UPROPERTY(EditDefaultsOnly, Category= Platforms)
	float StartSpeed = 500;
	
	UPROPERTY(EditDefaultsOnly, Category= Platforms)
	float SpeedIncrease = 10;
	
	UPROPERTY(EditDefaultsOnly, Category= Platforms)
	float MaxSpeed = 1000;

	UPROPERTY(EditDefaultsOnly, Category= Platforms)
	float SpeedIncreaseTime = 3;
	
	UPROPERTY(EditDefaultsOnly, Category= Platforms)
	TSubclassOf<AMovingPlatform> PlatformBP;

	UPROPERTY(EditDefaultsOnly, Category= UI)
	TSubclassOf<UGameHudWidget> HudWidgetBP;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCoinCollected OnScoreChange;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPlayerHit OnPlayerHit;

	UPROPERTY()
	TArray<double> LanePositions;
	
	UPROPERTY()
	float Score = 0;

	UPROPERTY()
	bool IsObstacleWave = false;
	
	UFUNCTION(BlueprintCallable)
	void AddScore(float Value);

	USceneComponent* GetNextSpawnPoint() const { return NextSpawnPosition; }

	float GetSpeed() const { return CurrentPlatformSpeed; }

	void SetNextSpawnPoint(USceneComponent* Value) { NextSpawnPosition = Value; }

private:
	
	UPROPERTY()
	float CurrentPlatformSpeed = 500;
	
	UPROPERTY()
	USceneComponent* NextSpawnPosition = nullptr;

	UPROPERTY(VisibleInstanceOnly)
	UGameHudWidget* HudWidget = nullptr;

	UPROPERTY()
	FTimerHandle SpeedTimerHandle;
	
	UFUNCTION()
	void AddSpeed();
	
	AMovingPlatform* SpawnPlatform(const bool SpawnObstacles);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
