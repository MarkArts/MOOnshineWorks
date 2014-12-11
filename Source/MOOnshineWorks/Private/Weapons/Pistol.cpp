// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Pistol.h"


APistol::APistol(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Name = "Pistol";
	Id = 14.f;

	CharacterEquipOffset = FVector(20.f, 40.f, -20.f);
	CharacterEquipRotation = FRotator(0.f, 80.f, 0.f);

	SpreadAngle = 0.f;
	ShootCooldown = 0.8f;
}

void APistol::Use()
{
	if (HasAmmo())
	{
		if (CanShoot())
		{
			Shoot();
			UseAmmo();
		}
	}
}

void APistol::Shoot()
{
	FVector SpawnLocation = RootComponent->GetSocketLocation("BulletSpawn");
	AProjectile* Projectile = SpawnProjectile(SpawnLocation, GetTarget());
	Super::Shoot();
}