// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_BasicController.h"
//#include "AI_BasicEnemy.h"
#include "AI_PegEnemyLight.h"
#include "AI_PegEnemyDark.h"
#include "AI_GarbageEnemy.h"
#include "AI_BookEnemy.h"
#include "AI_MeleeController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_MeleeController : public AAI_BasicController
{
	GENERATED_BODY()
public:
	AAI_MeleeController(const class FObjectInitializer& PCIP);

	virtual void AttackPlayer() override;

	virtual void Patrol() override;

	virtual void GoActive() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_PegEnemyLight> PegLightEnemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_PegEnemyDark> PegDarkEnemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_GarbageEnemy> GarbageEnemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_BookEnemy> BookEnemyClass;
};
