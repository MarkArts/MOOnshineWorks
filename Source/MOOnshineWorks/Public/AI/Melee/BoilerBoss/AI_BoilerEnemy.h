// Creative Common Share Alike

#pragma once

#include "AI_BasicEnemy.h"
#include "AI_MeleeEnemy.h"
#include "AI_BoilerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BoilerEnemy : public AAI_MeleeEnemy
{
	GENERATED_BODY()
public:
	AAI_BoilerEnemy(const class FObjectInitializer& PCIP);
};
