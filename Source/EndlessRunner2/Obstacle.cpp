// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "Kismet/GameplayStatics.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(RootComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComp);
	Mesh->SetCollisionProfileName(FName("OverlapOnlyPawn"));
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnComponentBeginOverlap);
}

void AObstacle::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->Tags.Contains("Coin"))
		return;
	
	UGameplayStatics::ApplyDamage(OtherActor, 1, GetInstigatorController(), this, UDamageType::StaticClass());
	Destroy();
}
 