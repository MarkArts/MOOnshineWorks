﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "AI_BasicController.h"
#include "AI_PegEnemyDark.h"
#include "AI_BasicEnemy.h"
#include "AI_MeleeController.h"
#include "AI_PegControllerDark.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_PegControllerDark : public AAI_MeleeController
{
	GENERATED_UCLASS_BODY()

	virtual void AttackPlayer() override;

	virtual void Patrol() override;

	virtual void GoActive() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_PegEnemyDark> EnemyClass;
};