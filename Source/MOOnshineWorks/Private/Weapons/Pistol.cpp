// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Pistol.h"


APistol::APistol(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Name = "Pistol";
	Id = 14.f;

	/*static ConstructorHelpers::FClassFinder<AProjectile> BP_Projectile(TEXT("/Game/Blueprints/BP_Projectile"));
	ProjectileClass = BP_Projectile.Class;*/

	MagazineCapacity = 15.f;
	MagazineLoadCount = MagazineCapacity;
	DamageValue = 5.f;
	ReloadTime = 2.f;
	SpreadAngle = 0.f;
	ShootCooldown = 0.8f;
	Reloading = false;
}

void APistol::Use()
{
	if (!Reloading)
	{
		if (HasAmmo())
		{
			if (CanShoot())
			{
				Shoot();
				MagazineCountDecrement();
			}
		}
		else
		{
			Reload();
		}
	}
}

void APistol::Shoot()
{
	FVector SpawnLocation = RootComponent->GetSocketLocation("BulletSpawn");
	AProjectile* Projectile = SpawnProjectile(SpawnLocation, GetTarget());
	SetLastShotTime();
	OnUse();
}

bool APistol::HasAmmo()
{
	return MagazineLoadCount > 0;
}

void APistol::MagazineCountDecrement()
{
	MagazineLoadCount = FMath::Max(0.f, MagazineLoadCount - 1);
}