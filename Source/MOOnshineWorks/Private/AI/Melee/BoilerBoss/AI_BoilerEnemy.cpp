// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "AI_BoilerMeleeController.h"
#include "AI_BoilerEnemy.h"

AAI_BoilerEnemy::AAI_BoilerEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_BoilerMeleeController::StaticClass();
}


