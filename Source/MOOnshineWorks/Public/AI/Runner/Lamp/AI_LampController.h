// Creative Common Share Alike

#pragma once

#include "AI_RunnerController.h"
#include "AI_LampEnemy.h"
#include "AI_LampController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_LampController : public AAI_RunnerController
{
	GENERATED_BODY()
public:
	AAI_LampController(const class FObjectInitializer& PCIP);

	virtual void GoActive() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubclassOf<AAI_LampEnemy> EnemyClass;
};
