// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Basic/AI_BasicEnemy.h"
#include "AI_PianoEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_PianoEnemy : public AAI_BasicEnemy
{
	GENERATED_BODY()
public:
	AAI_PianoEnemy(const class FObjectInitializer& PCIP);

	/** PushBack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	float PianoPushPower;
};
