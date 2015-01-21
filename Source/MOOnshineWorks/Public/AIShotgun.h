// Creative Common Share Alike

#pragma once

#include "Weapons/Gun.h"
#include "AIShotgun.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAIShotgun : public AGun
{
	GENERATED_BODY()	
public:
	AAIShotgun(const class FObjectInitializer& PCIP);

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = AIGun)
	USphereComponent* GunSphere;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = AIGun)
	int32 PelletCount;

	//virtual void Use() override;
	//virtual void Shoot() override;
	//virtual FVector GetTarget() override;
};
