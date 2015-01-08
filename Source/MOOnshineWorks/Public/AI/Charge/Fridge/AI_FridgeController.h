// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Charge/AI_ChargeController.h"
#include "AI_FridgeEnemy.h"
#include "AI_ChargeController.h"
#include "AI_FridgeController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_FridgeController : public AAI_ChargeController
{
	GENERATED_UCLASS_BODY()

	virtual void AttackPlayer() override;

	virtual void Patrol() override;

	virtual void GoActive() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_FridgeEnemy> EnemyClass;
};
