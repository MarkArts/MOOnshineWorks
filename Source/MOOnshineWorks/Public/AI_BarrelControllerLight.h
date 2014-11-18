// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_BasicController.h"
#include "AI_BarrelEnemyLight.h"
#include "AI_BasicEnemy.h"
#include "AI_BarrelControllerLight.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BarrelControllerLight : public AAI_BasicController
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void AttackPlayer();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SpeedUp();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void BarrelPatrol();
};
