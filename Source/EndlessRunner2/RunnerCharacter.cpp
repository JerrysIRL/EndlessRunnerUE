// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"
#include "RunnerGameMode.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SpringArm->SetupAttachment(GetMesh());
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ARunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}


void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARunnerCharacter::Jump);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ARunnerCharacter::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ARunnerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ARunnerCharacter::Roll);
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

void ARunnerCharacter::Roll()
{
	if (GetCharacterMovement()->IsFalling() || GetMesh()->GetAnimInstance()->Montage_IsPlaying(NULL))
		return;
	const float animDuration = PlayAnimMontage(RollMontage, 1.5f, NAME_None);
	Crouch();
	GetWorldTimerManager().SetTimer(rollHandle, this, &ARunnerCharacter::ResetRoll, animDuration, false);
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Crouching!"));
}

void ARunnerCharacter::ResetRoll() { UnCrouch(); }
