// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Basic/AI_BasicController.h"
#include "AI_PianoEnemy.h"
#include "AI_ChargeController.h"
#include "AI_PianoController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_PianoController : public AAI_ChargeController
{
	GENERATED_BODY()
public:
	AAI_PianoController(const class FObjectInitializer& PCIP);

	virtual void AttackPlayer() override;

	virtual void Patrol() override;

	virtual void GoActive() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_PianoEnemy> EnemyClass;
};
