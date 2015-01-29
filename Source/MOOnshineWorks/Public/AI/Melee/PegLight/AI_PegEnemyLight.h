// Creative Common Share Alike

#pragma once

#include "GameFramework/Character.h"
#include "AI_BasicEnemy.h"
#include "AI_BasicController.h"
#include "AI_MeleeEnemy.h"
#include "AI_PegEnemyLight.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_PegEnemyLight : public AAI_MeleeEnemy
{
	GENERATED_BODY()
public:
	AAI_PegEnemyLight(const class FObjectInitializer& PCIP);
};
