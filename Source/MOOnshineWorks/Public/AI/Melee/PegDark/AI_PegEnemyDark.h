// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AI_BasicEnemy.h"
#include "AI_BasicController.h"
#include "AI_MeleeEnemy.h"
#include "AI_PegEnemyDark.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_PegEnemyDark : public AAI_MeleeEnemy
{
	GENERATED_BODY()
public:
	AAI_PegEnemyDark(const class FObjectInitializer& PCIP);
};
