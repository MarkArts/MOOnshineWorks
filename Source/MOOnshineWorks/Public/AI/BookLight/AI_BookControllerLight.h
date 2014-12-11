// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AI_BasicController.h"
#include "AI_BookEnemyLight.h"
#include "AI_BasicEnemy.h"
#include "AI_BookControllerLight.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BookControllerLight : public AAI_BasicController
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = AIBookBehavior)
	void BookPatrol();

	UFUNCTION(BlueprintCallable, Category = AIBookBehavior)
	void BookAttackPlayer();

	UFUNCTION(BlueprintCallable, Category = AIBookBehavior)
	void GoBackToOriginalPosition();

	UFUNCTION(BlueprintCallable, Category = AIBookBehavior)
	void BookGoActive();
};
