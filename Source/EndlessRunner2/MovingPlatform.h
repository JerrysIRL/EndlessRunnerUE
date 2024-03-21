// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	JumpRoll,
	Roll,
	Empty
};

UCLASS()
class ENDLESSRUNNER2_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	UPROPERTY(EditDefaultsOnly, Category=Lanes)
	UArrowComponent* LeftLane;

	UPROPERTY(EditDefaultsOnly, Category=Lanes)
	UArrowComponent* CenterLane;

	UPROPERTY(EditDefaultsOnly, Category=Lanes)
	UArrowComponent* RightLane;

	UPROPERTY()
	TArray<UArrowComponent*> Lanes;

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
	
	UPROPERTY(EditDefaultsOnly, Category=Obstacles)
	TSubclassOf<AObstacle> JumpRollObstacleBP;
	
	UFUNCTION()
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	TArray<EObstacleTypes> DodgableObstacles = {Coin, Roll, Wall, JumpRoll, Jump, Empty};

	FActorSpawnParameters spawnParams;

	TArray<EObstacleTypes> ChooseRandomObstacles(int32 NumObstacles);
	
	FTimerHandle MoveHandle;

	void MovePlatformToEnd();
	
	bool IsAllWalls(TArray<EObstacleTypes> RandomObstacles);
	
public:
	USceneComponent* GetSpawnPosition() const;
	
	void ResetPlatform() const;
	
	virtual void Tick(float DeltaTime) override;
};
