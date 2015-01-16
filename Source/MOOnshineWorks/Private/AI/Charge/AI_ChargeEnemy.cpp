// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "AI_ChargeController.h"
#include "AI_ChargeEnemy.h"

AAI_ChargeEnemy::AAI_ChargeEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_ChargeController::StaticClass();

	PushPower = 0;
}


