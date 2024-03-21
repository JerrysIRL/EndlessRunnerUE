// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunnerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ARunnerGameMode;

UCLASS()
class ENDLESSRUNNER2_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	
	ARunnerCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= Animations)
	UAnimMontage* RollMontage;

	UPROPERTY()
	int CurrentLane = 1;

	UFUNCTION(BlueprintCallable)
	void MoveCharacterUpdate(float t);

	/* Timeline event for Blueprints */
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeLane();

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY()
	ARunnerGameMode* GameMode = nullptr;
	
	virtual void BeginPlay() override;

	void MoveLeft();

	void Roll();

	void MoveRight();

	FTimerHandle rollHandle;

	void ResetRoll();
};
