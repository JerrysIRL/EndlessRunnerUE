// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"

#include "RunnerGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ARunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}


void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARunnerCharacter::Jump);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ARunnerCharacter::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ARunnerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ARunnerCharacter::Crouch);
}

void ARunnerCharacter::MoveLeft()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Moving Left!"));
	CurrentLane = FMath::Clamp(CurrentLane - 1, 0, 2);
	SetActorLocation(GameMode->LanePositions[CurrentLane]);
}

void ARunnerCharacter::MoveRight()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Moving right!"));
	CurrentLane = FMath::Clamp(CurrentLane + 1, 0, 2);
	SetActorLocation(GameMode->LanePositions[CurrentLane]);
}

void ARunnerCharacter::Crouch()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Crouching!"));
}
