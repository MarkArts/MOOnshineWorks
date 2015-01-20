// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MOOnshineWorksGameMode.h"
#include "AI_PegEnemyDark.h"
#include "AI_BasicEnemy.h"
#include "AI_BasicController.h"
#include "AI_PegEnemyLight.h"
#include "AI_MeleeController.h"
#include "AI_PianoEnemy.h"
#include "AI_FridgeEnemy.h"
#include "AI_BarrelEnemy.h"
#include "SpawnEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ASpawnEnemy : public AActor
{
	GENERATED_UCLASS_BODY()
		/*
public:
	ASpawnEnemy(const class FObjectInitializer& PCIP);

	UFUNCTION(BlueprintCallable, Category = "Moonshine")
	void SpawnRandomEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MOOnshine)
	TSubclassOf<AAI_BasicEnemy> EnemyClass;

	class UBehaviorTree * BehaviorTree;

	UPROPERTY(EditAnywhere, Category = MOOnshine)
	bool ShouldSpawnEnemies;

	//Melee
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_PegEnemyLight> PegLightEnemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_PegEnemyDark> PegDarkEnemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_GarbageEnemy> GarbageEnemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_BookEnemy> MeleeBookEnemyClass;

	//Range
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_BookEnemyLight> RangeBookEnemyClass;

	//Charge
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_PianoEnemy> PianoEnemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_FridgeEnemy> FridgeEnemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_BarrelEnemy> BarrelEnemyClass;

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
	*/
};
