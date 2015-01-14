// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_BasicEnemy.h"
#include "AI_RunnerEnemy.h"
#include "AI_VoodooEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_VoodooEnemy : public AAI_RunnerEnemy
{
	GENERATED_BODY()
public:
	AAI_VoodooEnemy(const class FObjectInitializer& PCIP);
};
