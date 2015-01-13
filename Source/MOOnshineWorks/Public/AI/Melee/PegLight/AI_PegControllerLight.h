// Creative Common Share Alike

#pragma once

#include "AI_PegEnemyLight.h"
#include "AI_BasicEnemy.h"
#include "AI_MeleeController.h"
#include "AI_PegControllerLight.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_PegControllerLight : public AAI_MeleeController
{
	GENERATED_UCLASS_BODY()

	virtual void AttackPlayer() override;

	virtual void Patrol() override;

	virtual void GoActive() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_PegEnemyLight> EnemyClass;
};
