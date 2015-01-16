// Creative Common Share Alike

#pragma once

#include "AI_BasicEnemy.h"
#include "AI_ChargeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_ChargeEnemy : public AAI_BasicEnemy
{
	GENERATED_BODY()
public:	
	AAI_ChargeEnemy(const class FObjectInitializer& PCIP);

	/** PushBack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	float PushPower;
};
