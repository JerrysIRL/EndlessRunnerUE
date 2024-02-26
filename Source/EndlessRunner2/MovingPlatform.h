// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DSP/Chorus.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class AObstacle;
class ARunnerGameMode;
class UBoxComponent;
class UArrowComponent;

UENUM(BlueprintType)
enum EObstacleTypes
{
	Wall,
	Coin,
	Jump,
	Roll,
	Empty
};

UCLASS()
class ENDLESSRUNNER2_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

	FTimerHandle MoveHandle;

	bool IsAllWalls(TArray<EObstacleTypes> RandomObstacles);

public:
	AMovingPlatform();

	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* LeftLane;

	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* CenterLane;

	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* RightLane;

	UPROPERTY()
	TArray<UArrowComponent*> Lanes;

	UPROPERTY(EditDefaultsOnly)
	float speed = 100.0f;

	UFUNCTION()
	void SpawnObstacleWave();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	ARunnerGameMode* GameMode;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftEdge;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightEdge;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftBarrier;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightBarrier;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* SpawnPosition;

	UPROPERTY(EditDefaultsOnly, Category=Obstacles)
	TSubclassOf<AObstacle> WallBP;
	
	UPROPERTY(EditDefaultsOnly, Category=Obstacles)
	TSubclassOf<AObstacle> CoinBP;
	
	UPROPERTY(EditDefaultsOnly, Category=Obstacles)
	TSubclassOf<AObstacle> RollObstacleBP;
	
	UPROPERTY(EditDefaultsOnly, Category=Obstacles)
	TSubclassOf<AObstacle> JumpObstacleBP;

	TArray<EObstacleTypes> DodgableObstacles = {Coin, Roll, Jump, Empty};

	FActorSpawnParameters spawnParams;

	UFUNCTION()
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	TArray<EObstacleTypes> ChooseRandomObstacles(int32 NumObstacles);

	void MovePlatformToEnd();

public:
	virtual void Tick(float DeltaTime) override;

	USceneComponent* GetSpawnPosition() const;
};
