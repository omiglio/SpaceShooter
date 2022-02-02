// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipController.h"
#include "Components/BoxComponent.h"
#include "BulletController.h"
#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = 
		CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &
		AShipController::OnOverlap);
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AShipController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() +
		Speed * CurrentVelocity * DeltaTime;

		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void AShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, 
		&AShipController::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, 
		&AShipController::Move_YAxis);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AShipController::OnShoot);
	InputComponent->BindAction("ReStart", IE_Pressed, this, &
		AShipController::OnRestart).bExecuteWhenPaused = true;
}

void AShipController::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue * 100.0f;
}

void AShipController::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue * 100.0f;
}

void AShipController::OnShoot()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FVector(Location) = GetActorLocation(); // Spawn bullet in exact position where ship is located.
		World->SpawnActor<ABulletController>
		(BulletBlueprint, Location, FRotator::ZeroRotator);
	}

}

void AShipController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor
* OtherActor, UPrimitiveComponent* OtherComponent, int32
OtheBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AEnemyController::StaticClass()))
	{
		Died = true;

		this->SetActorHiddenInGame(true);

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AShipController::OnRestart()
{
	if (Died)
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->
			GetName()), false);
	}
}
