// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI_BasicController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BasicController : public AAIController
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(transient)
	TSubobjectPtr<class UBlackboardComponent> BlackboardComp;

	UPROPERTY(transient)
	TSubobjectPtr<class UBehaviorTreeComponent> BehaviorComp;

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SearchForEnemy();

	void SetEnemy(class APawn *InPawn);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SetOriginalPosition();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void ChangeAIDarkLight(bool DarkLight);

	virtual void Possess(class APawn *InPawn);

	virtual void Tick(float DeltaSeconds) OVERRIDE;

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void FoundPlayer();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void LostPlayer();

	uint8 StateAI;					//Int
	uint8 EnemyKeyID;				//Object
	uint8 EnemyLocationID;			//Vector
	uint8 EnemyDistance;			//Float
	uint8 SetPatrolRoute;			//Vector
	uint8 WhereShouldAIPatrolTo;    //Float
	uint8 OriginalPosition;			//Vector
	uint8 GotEnemyAsTarget;			//Bool
	uint8 LastSeenPosition;			//Vector
	
	//Animations setten!
	UFUNCTION(BlueprintCallable, Category = Animation)
	void SetIdleAnimation();

	UFUNCTION(BlueprintCallable, Category = Animation)
	void SetPatrollingAnimation();

	UFUNCTION(BlueprintCallable, Category = Animation)
	void SetAttackAnimation();

	UFUNCTION(BlueprintCallable, Category = AIState)
	void AISetPatrolState();

	UFUNCTION(BlueprintCallable, Category = AIState)
	void AISetAttackState();

	UFUNCTION(BlueprintCallable, Category = AIState)
	void AISetSearchState();
};
