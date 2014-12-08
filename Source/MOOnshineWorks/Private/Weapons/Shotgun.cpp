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
	
	SpreadAngle = 20.f;
	ShootCooldown = 1.2f;
	PelletCount = 6.f;
}

void AShotgun::Use()
{
	if (HasAmmo())
	{
		if (CanShoot())
		{
			Shoot();
		}
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