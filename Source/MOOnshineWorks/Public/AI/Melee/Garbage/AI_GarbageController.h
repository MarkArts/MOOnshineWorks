// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Melee/AI_MeleeController.h"
#include "AI_GarbageEnemy.h"
#include "AI_GarbageController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_GarbageController : public AAI_MeleeController
{
	GENERATED_UCLASS_BODY()

	virtual void AttackPlayer() override;

	virtual void Patrol() override;

	virtual void GoActive() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_GarbageEnemy> EnemyClass;
};
