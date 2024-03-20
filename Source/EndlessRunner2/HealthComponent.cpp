
// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "RunnerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ARunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
	GameMode->OnPlayerHit.Broadcast(CurrentHealth);
	if(CurrentHealth <= 0)
	{
		GetOwner()->Destroy();
	}
}
