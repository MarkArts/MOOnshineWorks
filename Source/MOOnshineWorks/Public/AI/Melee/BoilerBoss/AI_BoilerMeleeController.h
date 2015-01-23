// Creative Common Share Alike

#pragma once

#include "AI_BoilerEnemy.h"
#include "AI_BasicEnemy.h"
#include "AI_MeleeController.h"
#include "AI_BoilerMeleeController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BoilerMeleeController : public AAI_MeleeController
{
	GENERATED_BODY()
public:
	AAI_BoilerMeleeController(const class FObjectInitializer& PCIP);

	virtual void AttackPlayer() override;

	virtual void Patrol() override;
};
