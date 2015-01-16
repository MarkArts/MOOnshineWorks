// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "AI_LampEnemy.h"
#include "AI_LampController.h"

AAI_LampEnemy::AAI_LampEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_LampController::StaticClass();
}



