// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunnerCharacter.generated.h"

class ARunnerGameMode;

UCLASS()
class ENDLESSRUNNER2_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY()
	ARunnerGameMode* GameMode = nullptr;
	
public:
	// Sets default values for this character's properties
	ARunnerCharacter();
	
	UPROPERTY()
	int CurrentLane = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveLeft();

	void Crouch();

	void MoveRight();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
