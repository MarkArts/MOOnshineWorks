// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Bazooka.h"


ABazooka::ABazooka(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Name = "Bazooka";
	Id = 16.f;

	CharacterEquipOffset = FVector(20.f, 17.5f, -40.f);
	CharacterEquipRotation = FRotator(0.f, 80.f, 0.f);

	SpreadAngle = 5.f;
	ShootCooldown = 5.f;
}

void ABazooka::Use()
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

void ABazooka::Shoot()
{
	FVector SpawnLocation = RootComponent->GetSocketLocation("BulletSpawn");
	FVector Target = GetTarget();
	AProjectile* Projectile = SpawnProjectile(SpawnLocation, Target);
	Super::Shoot();
}