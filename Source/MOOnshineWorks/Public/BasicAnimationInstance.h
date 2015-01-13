// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "BasicAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API UBasicAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UBasicAnimationInstance(const class FObjectInitializer& PCIP);

	/** Check if Patrolling animation has to be used */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIAnimation)
	bool AIPatrolling;

	/* Check if AI is attacking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIAnimation)
	bool AIAttacking;

	/* Check if AI is idle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIAnimation)
	bool AIIdle;

	/* Check if AI is killed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIAnimation)
	bool AIDeath;

	/* Check if AI is preparing charge */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIAnimation)
	bool AICharging;
};
