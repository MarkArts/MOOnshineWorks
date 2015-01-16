// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "AI_RunnerEnemy.h"
#include "AI_RunnerController.h"

AAI_RunnerEnemy::AAI_RunnerEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_RunnerController::StaticClass();

	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		static ConstructorHelpers::FClassFinder<ACollectible> PlayerPawnBPClass(TEXT("/Game/Blueprints/Pickups/BP_AAmmoBarrel"));
		if (PlayerPawnBPClass.Class != NULL)
		{
			DropItem = PlayerPawnBPClass.Class;
		}
	}

	TimerActive = 0;
}


