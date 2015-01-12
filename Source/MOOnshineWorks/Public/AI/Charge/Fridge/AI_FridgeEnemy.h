// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Basic/AI_BasicEnemy.h"
#include "AI_FridgeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_FridgeEnemy : public AAI_BasicEnemy
{
	GENERATED_UCLASS_BODY()

	/** PushBack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	float PianoPushPower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AIStats)
	TSubobjectPtr<UAudioComponent> ChargeAudio;
};
