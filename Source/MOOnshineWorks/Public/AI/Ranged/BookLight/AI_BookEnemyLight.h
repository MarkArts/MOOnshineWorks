// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AI_BasicEnemy.h"
#include "AI_BasicController.h"
#include "AIBookGun.h"
#include "AI_BookEnemyLight.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BookEnemyLight : public AAI_BasicEnemy
{
	GENERATED_UCLASS_BODY()

	virtual void ReceiveBeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIGun)
	TSubclassOf<AAIBookGun> GunClass;

	AAIBookGun* Gun;
};
