// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletController.h"
#include "Components/BoxComponent.h"
#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShooterGameMode.h"

// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootBox->SetGenerateOverlapEvents(true);
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &
		ABulletController::OnOverlap);
}

// Called when the game starts or when spawned
void ABulletController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABulletController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;
	SetActorLocation(NewLocation);

	if (NewLocation.X < -600.0f)
	{
		this->Destroy();

		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->
			IncrementScore();
	}
}

void ABulletController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor
	* OtherActor, UPrimitiveComponent* OtherComponent, int32
	OtheBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AEnemyController::StaticClass()))
	{
		this->Destroy();
		OtherActor->Destroy();
	}
}

