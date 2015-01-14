// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Basic/AI_BasicController.h"
#include "AI_BarrelEnemy.h"
#include "AI_ChargeController.h"
#include "AI_BarrelController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BarrelController : public AAI_ChargeController
{
	GENERATED_BODY()
public:
	AAI_BarrelController(const class FObjectInitializer& PCIP);

    virtual void AttackPlayer() override;
    
    virtual void Patrol() override;

	virtual void GoActive() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_BarrelEnemy> EnemyClass;
};