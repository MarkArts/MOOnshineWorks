// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Character.h"
#include "AI_BasicEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BasicEnemy : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** Health */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIStats)
	float Health;

	/** Defense */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIStats)
	float Defense;

	/** Speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIStats)
	float Speed;

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* Behavior;

	void StartSprint();

	void StartWalk();

	UFUNCTION(BlueprintCallable, Category = AIStats)
	void ChangeLightDark(bool CurrentDarkLight);
};
