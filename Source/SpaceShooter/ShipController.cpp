// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipController.h"

// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

// Called to bind functionality to input
void AShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

