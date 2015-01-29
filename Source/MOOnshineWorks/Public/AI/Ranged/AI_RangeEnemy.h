// Creative Common Share Alike

#pragma once

#include "AI/Basic/AI_BasicEnemy.h"
#include "AI_RangeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_RangeEnemy : public AAI_BasicEnemy
{
	GENERATED_BODY()
public:
	AAI_RangeEnemy(const class FObjectInitializer& PCIP);
	
	virtual void ReceiveBeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIGun)
	TSubclassOf<AGun> GunClass;

	AGun* Gun;
};
