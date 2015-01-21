// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_BasicController.h"
#include "AI_VoodooEnemy.h"
#include "AI_LampEnemy.h"
#include "AI_RunnerController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_RunnerController : public AAI_BasicController
{
	GENERATED_UCLASS_BODY()
		
//public:
	//AAI_RunnerController(const class FObjectInitializer& PCIP);
	/*

	UFUNCTION(BlueprintCallable, Category = Behavior)
	virtual void RunAway();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	virtual void TimeIsUp();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	virtual void ReduceTimer();

	virtual void GoActive() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_VoodooEnemy> VoodooEnemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_LampEnemy> LampEnemyClass;
	*/
};
