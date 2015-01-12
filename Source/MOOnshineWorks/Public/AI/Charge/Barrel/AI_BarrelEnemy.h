// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AI_BasicEnemy.h"
#include "AI_BasicController.h"
#include "AI_BarrelEnemy.generated.h"
/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BarrelEnemy : public AAI_BasicEnemy
{
	GENERATED_UCLASS_BODY()

	/** PushBack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	float PianoPushPower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AIStats)
	TSubobjectPtr<UAudioComponent> ChargeAudio;
};
