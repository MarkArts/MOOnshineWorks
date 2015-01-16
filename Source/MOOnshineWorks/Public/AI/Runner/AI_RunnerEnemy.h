// Creative Common Share Alike

#pragma once

#include "AI_BasicEnemy.h"
#include "AI_RunnerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_RunnerEnemy : public AAI_BasicEnemy
{
	GENERATED_BODY()	

public:
	AAI_RunnerEnemy(const class FObjectInitializer& PCIP);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
	TSubclassOf<ACollectible> DropItem;

	/** TimerActive */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	float TimerActive;
};
