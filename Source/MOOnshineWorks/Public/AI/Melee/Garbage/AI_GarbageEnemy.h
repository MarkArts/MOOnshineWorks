// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Basic/AI_BasicEnemy.h"
#include "AI_MeleeEnemy.h"
#include "AI_GarbageEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_GarbageEnemy : public AAI_MeleeEnemy
{
	GENERATED_BODY()
public:
	AAI_GarbageEnemy(const class FObjectInitializer& PCIP);
};
