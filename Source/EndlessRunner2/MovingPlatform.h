// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class ARunnerGameMode;
class UBoxComponent;
class UArrowComponent;

UCLASS()
class ENDLESSRUNNER2_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

	FTimerHandle MoveHandle;

public:
	AMovingPlatform();

	UPROPERTY(EditDefaultsOnly, meta=(MakeEditWidget = true))
	FVector LeftLane;

	UPROPERTY(EditDefaultsOnly, meta=(MakeEditWidget = true))
	FVector CenterLane;

	UPROPERTY(EditDefaultsOnly, meta=(MakeEditWidget = true))
	FVector RightLane;

	UPROPERTY(EditDefaultsOnly)
	float speed = 100.0f;
	
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

	UFUNCTION()
	void OnTriggerBoxOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void MovePlatformToEnd();

public:
	
	virtual void Tick(float DeltaTime) override;

	FVector GetSpawnPosition() const;
};
