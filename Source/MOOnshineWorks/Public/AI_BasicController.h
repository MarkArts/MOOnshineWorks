// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI_BasicEnemy.h"
#include "AI_BasicController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BasicController : public AAIController
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(transient)
	TSubobjectPtr<class UBlackboardComponent> BlackboardComp;

	UPROPERTY(transient)
	TSubobjectPtr<class UBehaviorTreeComponent> BehaviorComp;

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SearchForEnemy();

	void SetEnemy(class APawn *InPawn);

	virtual void Possess(class APawn *InPawn);

	uint8 EnemyKeyID;				//Object
	uint8 EnemyLocationID;			//Vector
	uint8 EnemyDistance;			//Float
	uint8 SetPatrolRoute;			//Vector
	uint8 WhereShouldAIPatrolTo;    //Float
};
