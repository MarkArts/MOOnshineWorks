// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AI_BarrelEnemy.h"
#include <sstream>
#include "SpawnEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ASpawnEnemy : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Moonshine")
	void SpawnRandomEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MOOnshine)
	TSubclassOf<AAI_BarrelEnemy> EnemyClass;

	class UBehaviorTree * BehaviorTree;

	void SetTime(float Time);

	UPROPERTY(EditAnywhere, Category = MOOnshine)
	float Time;

	UPROPERTY(EditAnywhere, Category = MOOnshine)
	FString Enemies;

protected:

	virtual void ReceiveBeginPlay() override;
};
