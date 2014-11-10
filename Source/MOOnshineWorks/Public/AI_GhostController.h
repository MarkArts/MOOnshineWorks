// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AI_Ghost.h"
#include "GameFramework/Character.h"
#include "MOOnshineWorksCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI_GhostController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_GhostController : public AAIController
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(transient)
	TSubobjectPtr<class UBlackboardComponent> BlackboardComp;

	UPROPERTY(transient)
	TSubobjectPtr<class UBehaviorTreeComponent> BehaviorComp;

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SearchForEnemy();

	virtual void Possess(class APawn *InPawn);

	void SetEnemy(class APawn *InPawn);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void AttackPlayer();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void Patrol();

protected:

	uint8 EnemyKeyID;	   //Object
	uint8 EnemyLocationID; //Vector
	uint8 EnemyDistance;   //Float
	uint8 SetPatrolRoute;   //Vector

};
