// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"

#include "RunnerGameMode.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

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

void ARunnerCharacter::MoveCharacterUpdate(float t)
{
	auto CurrentLocation = GetActorLocation();
	CurrentLocation.Y = FMath::Lerp(CurrentLocation.Y, GameMode->LanePositions[CurrentLane], t);
	SetActorLocation(CurrentLocation);
}

void ARunnerCharacter::MoveLeft()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Moving Left!"));
	CurrentLane = FMath::Clamp(CurrentLane - 1, 0, 2);
	ChangeLane();
}

void ARunnerCharacter::MoveRight()	
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Moving right!"));
	CurrentLane = FMath::Clamp(CurrentLane + 1, 0, 2);
	ChangeLane();
}

void ARunnerCharacter::Crouch()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Crouching!"));
}
