// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Basic/AI_BasicController.h"
#include "AI_PianoController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_PianoController : public AAI_BasicController
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void AttackPlayer();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SpeedUp();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void PianoPatrol();
};
