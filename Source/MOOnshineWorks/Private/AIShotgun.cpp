// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "AIShotgun.h"

AAIShotgun::AAIShotgun(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	Name = "AAIShotgun";
	Id = 9.f;

	GunSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("GunSphere"));
	RootComponent = GunSphere;

	SpreadAngle = 30.f;
	ShootCooldown = 2.0f;
	PelletCount = 3;
}

void AAIShotgun::Use()
{
	if (CanShoot())
	{
		Shoot();
		SetLastShotTime();
	}
}

void AAIShotgun::Shoot()
{
	FVector SpawnLocation = GetOwner()->GetActorLocation();
	for (int32 I = 0; I < PelletCount; I++)
	{
		AProjectile* Projectile = SpawnProjectile(SpawnLocation, GetTarget());
	}
	OnUse();
}

FVector AAIShotgun::GetTarget()
{
	return GetEnemyTarget();
}