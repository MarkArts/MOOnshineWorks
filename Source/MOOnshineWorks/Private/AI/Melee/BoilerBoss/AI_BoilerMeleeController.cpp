// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "AI_BoilerMeleeController.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"
#include "AI_BoilerEnemy.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_BasicEnemy.h"

AAI_BoilerMeleeController::AAI_BoilerMeleeController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}
void AAI_BoilerMeleeController::AttackPlayer()
{
	Super::AttackPlayer();
}
void AAI_BoilerMeleeController::Patrol()
{
	Super::Patrol();
}


