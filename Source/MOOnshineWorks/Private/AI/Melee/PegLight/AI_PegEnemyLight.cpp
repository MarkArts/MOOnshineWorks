// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "AI_PegEnemyLight.h"
#include "AI_PegControllerLight.h"

AAI_PegEnemyLight::AAI_PegEnemyLight(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_PegControllerLight::StaticClass();
}


