// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipController.generated.h"

UCLASS()
class SPACESHOOTER_API AShipController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UShapeComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
	float Speed = 10.f;

	UPROPERTY(EditAnywhere,
		Category = "Spawning")
	TSubclassOf<class ABulletController>
		BulletBlueprint;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void OnShoot();

	FVector CurrentVelocity;
};
