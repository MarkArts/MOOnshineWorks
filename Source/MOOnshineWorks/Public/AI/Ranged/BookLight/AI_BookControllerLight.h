// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AI_BasicController.h"
#include "AI_BookEnemyLight.h"
#include "AI_RangeController.h"
#include "AI_BookControllerLight.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BookControllerLight : public AAI_RangeController
{
	GENERATED_UCLASS_BODY()

	virtual void Patrol() override;

	virtual void AttackPlayer() override;

	virtual void GoBackToOriginalPosition() override;

	virtual void GoActive() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_BookEnemyLight> EnemyClass;
};
