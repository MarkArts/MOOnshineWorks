// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_BasicController.h"
#include "AI_PegEnemyDark.h"
#include "AI_BasicEnemy.h"
#include "AI_PegControllerDark.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_PegControllerDark : public AAI_BasicController
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void AttackPlayer();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SpeedUp();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void PegPatrol();

	UFUNCTION(BlueprintCallable, Category = AIBookBehavior)
	void PegGoActive();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_PegEnemyDark> EnemyClass;
};
