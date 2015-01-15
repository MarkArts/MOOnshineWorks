// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "AI_PegControllerLight.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"
#include "AI_PegEnemyLight.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_BasicEnemy.h"

AAI_PegControllerLight::AAI_PegControllerLight(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void AAI_PegControllerLight::AttackPlayer()
{
	Super::AttackPlayer();
}
void AAI_PegControllerLight::Patrol()
{
	Super::Patrol();
}


