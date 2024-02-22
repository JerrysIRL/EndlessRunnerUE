// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "RunnerGameMode.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootComp = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(RootComp);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMesh->SetupAttachment(RootComp);
	
	SpawnPosition = CreateDefaultSubobject<UArrowComponent>("Arrow");
	SpawnPosition->SetupAttachment(RootComp);

	LeftEdge = CreateDefaultSubobject<UStaticMeshComponent>("LeftEdge");
	LeftEdge->SetupAttachment(StaticMesh);
	
	RightEdge = CreateDefaultSubobject<UStaticMeshComponent>("RightEdge");
	RightEdge->SetupAttachment(StaticMesh);
	
	LeftBarrier = CreateDefaultSubobject<UStaticMeshComponent>("LeftLane");
	LeftBarrier->SetupAttachment(StaticMesh);
	
	RightBarrier = CreateDefaultSubobject<UStaticMeshComponent>("RightLane");
	RightBarrier->SetupAttachment(StaticMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	CollisionBox->SetupAttachment(RootComp);
	
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ARunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMovingPlatform::OnTriggerBoxOverlap);
}

void AMovingPlatform::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	GetWorldTimerManager().SetTimer(MoveHandle,this, &AMovingPlatform::MovePlatformToEnd ,1.0f, false);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto desiredLocation = GetActorLocation() + -FVector::ForwardVector * speed * DeltaTime;
	SetActorLocation(desiredLocation);
}

USceneComponent* AMovingPlatform::GetSpawnPosition() const
{
	return this->SpawnPosition;
}

void AMovingPlatform::MovePlatformToEnd()
{
	SetActorLocation(GameMode->GetNextSpawnPoint()->GetComponentLocation());
	GameMode->SetNextSpawnPoint(SpawnPosition);
}

