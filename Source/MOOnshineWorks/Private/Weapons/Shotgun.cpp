// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Shotgun.h"


AShotgun::AShotgun(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Name = "Shotgun";
	Id = 15.f;

	/*static ConstructorHelpers::FClassFinder<AProjectile> BP_Projectile(TEXT("/Game/Blueprints/BP_Projectile"));
	ProjectileClass = BP_Projectile.Class;*/
	
	MagazineCapacity = 0.f;
	MagazineLoadCount = 6;
	DamageValue = 1.f;
	ReloadTime = 2.f;
	SpreadAngle = 20.f;
	ShootCooldown = 1.2f;
	Reloading = false;
	PelletCount = 6.f;
}

void AShotgun::Use()
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

void AShotgun::Shoot()
{
	FVector SpawnLocation = RootComponent->GetSocketLocation("BulletSpawn");
	FVector Target = GetTarget();
	for (int i = 0; i < PelletCount; i++)
	{
		AProjectile* Projectile = SpawnProjectile(SpawnLocation, Target);
	}
	SetLastShotTime();
	OnUse();
}

bool AShotgun::CanShoot()
{
	return MagazineLoadCount > 0;
}

void AShotgun::MagazineCountDecrement()
{
	MagazineLoadCount = FMath::Max(0.f, MagazineLoadCount - 1);
}