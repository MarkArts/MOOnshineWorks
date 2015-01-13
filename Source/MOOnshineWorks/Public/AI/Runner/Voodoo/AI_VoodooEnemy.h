// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Basic/AI_BasicEnemy.h"
#include "AI_VoodooEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_VoodooEnemy : public AAI_BasicEnemy
{
	GENERATED_BODY()
public:
	AAI_VoodooEnemy(const class FObjectInitializer& PCIP);

	/** TimerActive */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	float TimerActive;
};
