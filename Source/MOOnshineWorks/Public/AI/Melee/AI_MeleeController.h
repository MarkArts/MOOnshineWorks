// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Basic/AI_BasicController.h"
#include "AI_MeleeController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_MeleeController : public AAI_BasicController
{
	GENERATED_UCLASS_BODY()

	virtual void AttackPlayer() override;

	virtual void Patrol() override;

	virtual void GoActive() override;
};
