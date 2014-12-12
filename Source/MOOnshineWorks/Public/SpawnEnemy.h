// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MOOnshineWorksGameMode.h"
#include "AI_PegEnemyDark.h"
#include "AI_BasicEnemy.h"
#include "SpawnEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ASpawnEnemy : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AISpawnClass)
	TSubclassOf<AAI_BasicEnemy> PegEnemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AISpawnClass)
	TSubclassOf<AAI_BasicEnemy> BookEnemy;

	UFUNCTION(BlueprintCallable, Category = "Moonshine")
	void SpawnRandomEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MOOnshine)
	TSubclassOf<AAI_BasicEnemy> EnemyClass;

	class UBehaviorTree * BehaviorTree;

protected:

	void SetTime(float Time);

	UPROPERTY(EditAnywhere, Category = MOOnshine)
	bool Repeat;

	UPROPERTY(EditAnywhere, Category = MOOnshine)
	float Time;

	UPROPERTY(EditAnywhere, Category = MOOnshine)
	TArray<FString> Enemies;

protected:

	virtual void ReceiveBeginPlay() override;
};
