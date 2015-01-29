// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "AI_RangeController.h"
#include "AI_RangeEnemy.h"

AAI_RangeEnemy::AAI_RangeEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_RangeController::StaticClass();
}
void AAI_RangeEnemy::ReceiveBeginPlay()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	// Added GetMesh check becuase it randomly crashe dhere. No idea if this will fix anything and should be found out
	if (GunClass && GetMesh())
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunClass, SpawnParams);
		if (Gun)
		{
			Gun->SetActorLocation(GetMesh()->GetComponentLocation());
			Gun->AttachRootComponentTo(GetMesh());
		}
	}
	Super::ReceiveBeginPlay();
}


