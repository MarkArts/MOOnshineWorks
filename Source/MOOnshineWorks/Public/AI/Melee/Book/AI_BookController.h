// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_BookEnemy.h"
#include "AI_BasicEnemy.h"
#include "AI_MeleeController.h"
#include "AI_BookController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BookController : public AAI_MeleeController
{
	GENERATED_BODY()
public:
	AAI_BookController(const class FObjectInitializer& PCIP);

	virtual void AttackPlayer() override;

	virtual void Patrol() override;
};
