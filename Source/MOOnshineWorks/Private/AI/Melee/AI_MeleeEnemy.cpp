// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "AI_MeleeController.h"
#include "AI_MeleeEnemy.h"

AAI_MeleeEnemy::AAI_MeleeEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_MeleeController::StaticClass();
}



