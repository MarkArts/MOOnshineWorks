// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_RunnerController.h"
#include "AI_VoodooEnemy.h"
#include "AI_VoodooController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_VoodooController : public AAI_RunnerController
{
	GENERATED_BODY()
public:
	AAI_VoodooController(const class FObjectInitializer& PCIP);
};
