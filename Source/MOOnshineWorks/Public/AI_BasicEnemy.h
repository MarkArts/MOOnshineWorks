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

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* Behavior;
	
public:

	void StartSprint();

	void StartWalk();
};
