// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "Explosion.h"
#include "ExplosiveProjectile.h"

AExplosiveProjectile::AExplosiveProjectile(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	ExplosionRadius = 300.f;
	DoesPushback = false;
}
/*
void AExplosiveProjectile::HitActor(AActor* OtherActor)
{
	Destroy();
}*/

void AExplosiveProjectile::Destroyed()
{
	if (DeathBlueprint)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			AExplosion* Result = World->SpawnActor<AExplosion>(DeathBlueprint, RootComponent->GetComponentLocation(), RootComponent->GetComponentRotation());
			Result->DoesPushback = DoesPushback;
			Result->EffectRadius = ExplosionRadius;
			Result->DamageValue = DamageValue;
			Result->BeginPlay();
		}
	}
	Super::Destroyed();
}