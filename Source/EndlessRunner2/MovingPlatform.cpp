
#include "MovingPlatform.h"
#include "Obstacle.h"
#include "RunnerGameMode.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(RootComp);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMesh->SetupAttachment(RootComp);

	SpawnPosition = CreateDefaultSubobject<UArrowComponent>("Arrow");
	SpawnPosition->SetupAttachment(RootComp);

	LeftLane = CreateDefaultSubobject<UArrowComponent>("LeftLane");
	LeftLane->SetupAttachment(RootComp);

	RightLane = CreateDefaultSubobject<UArrowComponent>("RightLane");
	RightLane->SetupAttachment(RootComp);

	CenterLane = CreateDefaultSubobject<UArrowComponent>("CenterLane");
	CenterLane->SetupAttachment(RootComp);

	LeftEdge = CreateDefaultSubobject<UStaticMeshComponent>("LeftEdge");
	LeftEdge->SetupAttachment(StaticMesh);

	RightEdge = CreateDefaultSubobject<UStaticMeshComponent>("RightEdge");
	RightEdge->SetupAttachment(StaticMesh);

	LeftBarrier = CreateDefaultSubobject<UStaticMeshComponent>("LeftLineBarrier");
	LeftBarrier->SetupAttachment(StaticMesh);

	RightBarrier = CreateDefaultSubobject<UStaticMeshComponent>("RightLineBarrier");
	RightBarrier->SetupAttachment(StaticMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	CollisionBox->SetupAttachment(RootComp);
}


void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ARunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMovingPlatform::OnTriggerBoxOverlap);
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	Lanes = {LeftLane, CenterLane, RightLane};
}

void AMovingPlatform::SpawnObstacleWave()
{
	auto randomObstacles = ChooseRandomObstacles(3);
	for (int i = 0; i < randomObstacles.Num(); ++i)
	{
		AObstacle* obstacle = nullptr;
		FVector Pos = Lanes[i]->GetComponentLocation();
		switch (randomObstacles[i])
		{
		case Wall: obstacle = GetWorld()->SpawnActor<AObstacle>(WallBP, Pos, FRotator::ZeroRotator);
			break;
		case Coin: obstacle = GetWorld()->SpawnActor<AObstacle>(CoinBP, Pos, FRotator::ZeroRotator);
			break;
		case Jump: obstacle = GetWorld()->SpawnActor<AObstacle>(JumpObstacleBP, Pos, FRotator::ZeroRotator);
			break;
		case Roll: obstacle = GetWorld()->SpawnActor<AObstacle>(RollObstacleBP, Pos, FRotator::ZeroRotator);
			break;
		case JumpRoll: obstacle = GetWorld()->SpawnActor<AObstacle>(JumpRollObstacleBP, Pos, FRotator::ZeroRotator);
			break;
		case Empty: obstacle = GetWorld()->SpawnActor<AObstacle>(CoinBP, Pos, FRotator::ZeroRotator);
			break;
		}
		if (obstacle)
			obstacle->AttachToComponent(Lanes[i], FAttachmentTransformRules::KeepWorldTransform);
	}
}

bool AMovingPlatform::IsAllWalls(TArray<EObstacleTypes> RandomObstacles)
{
	for (const EObstacleTypes& ObstacleType : RandomObstacles)
	{
		if (ObstacleType != Wall)
			return false;
	}
	return true;
}

TArray<EObstacleTypes> AMovingPlatform::ChooseRandomObstacles(int32 NumObstacles)
{
	TArray<EObstacleTypes> RandomObstacles;

	for (int32 i = 0; i < NumObstacles; ++i)
	{
		const int32 RandomIndex = FMath::RandRange(0, DodgableObstacles.Num() - 1);
		RandomObstacles.Add(DodgableObstacles[RandomIndex]);
	}
	if (!IsAllWalls(RandomObstacles))
	{
		return RandomObstacles;
	}

	return ChooseRandomObstacles(NumObstacles);
}

void AMovingPlatform::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetWorldTimerManager().SetTimer(MoveHandle, this, &AMovingPlatform::MovePlatformToEnd, 1.0f, false);
}


void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto NewLocation = GetActorLocation() + -FVector::ForwardVector * GameMode->GetSpeed() * DeltaTime;
	SetActorLocation(NewLocation);
}

USceneComponent* AMovingPlatform::GetSpawnPosition() const
{
	return this->SpawnPosition;
}

void AMovingPlatform::ResetPlatform()
{
	TArray<AActor*> ChildrenActors;
	GetAttachedActors(ChildrenActors);
	for (auto* child : ChildrenActors)
		child->Destroy();
}

void AMovingPlatform::MovePlatformToEnd()
{
	SetActorLocation(GameMode->GetNextSpawnPoint()->GetComponentLocation());
	ResetPlatform();
	if (GameMode->IsObstacleWave)
	{
		SpawnObstacleWave();
	}
	GameMode->IsObstacleWave = !GameMode->IsObstacleWave;
	GameMode->SetNextSpawnPoint(SpawnPosition);
}
