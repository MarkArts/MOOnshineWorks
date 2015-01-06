// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Basic/AI_BasicController.h"
#include "AI_RangeController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_RangeController : public AAI_BasicController
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = Behavior)
	virtual void Patrol();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	virtual void AttackPlayer();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	virtual void GoBackToOriginalPosition();

	virtual void GoActive();
};
