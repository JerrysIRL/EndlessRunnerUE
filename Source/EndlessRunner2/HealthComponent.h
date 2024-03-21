// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


class ARunnerGameMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESSRUNNER2_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY()
	ARunnerGameMode* GameMode = nullptr;
	
public:	
	UHealthComponent();

	UPROPERTY(EditDefaultsOnly, Category=Health)
	float MaxHealth = 3;

	UPROPERTY()
	float CurrentHealth = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	
		
};
