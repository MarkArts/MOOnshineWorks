// Creative Common Share Alike

#pragma once

#include "AIProjectile.h"
#include "ExplosiveProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AExplosiveProjectile : public AAIProjectile
{
	GENERATED_BODY()

public:
	AExplosiveProjectile(const class FObjectInitializer& PCIP);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	bool DoesPushback;

	//virtual void HitActor(AActor* OtherActor) override;
	virtual void Destroyed() override;
};
