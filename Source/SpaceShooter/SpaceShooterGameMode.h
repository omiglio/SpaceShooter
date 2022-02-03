// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SpaceShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API ASpaceShooterGameMode : public AGameMode
{
	GENERATED_BODY()

	float MINIMUM_INTERVAL = 0.5f;
	float MAXIMUM_INTERVAL = 2.0F;
	float TIME_TO_MINIMUM_INTERVAL = 30.f;

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyController> EnemyBlueprint;

	float EnemyTimer;
	float GameTimer;

	void IncrementScore();
	void OnGameOver();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:

	int Score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};
