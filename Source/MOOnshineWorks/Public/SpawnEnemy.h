// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MOOnshineWorksGameMode.h"
#include "BlueprintLoader.h"
#include "AI_ClosetEnemyLight.h"
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
	TSubclassOf<AAI_ClosetEnemyLight> EnemyClass;

	class UBehaviorTree * BehaviorTree;

protected:

	void SetTime(float Time);

	UPROPERTY(EditAnywhere, Category = MOOnshine)
	float Time;

	virtual void ReceiveBeginPlay() override;
};
