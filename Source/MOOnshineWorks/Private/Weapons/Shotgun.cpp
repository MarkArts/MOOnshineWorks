// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Shotgun.h"


AShotgun::AShotgun(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Name = "Shotgun";
	Id = 15.f;

	CharacterEquipOffset = FVector(20.f, 40.f, -40.f);
	CharacterEquipRotation = FRotator(0.f, 70.f, 0.f);
	
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
			UseAmmo();
		}
	}
}

void AShotgun::Shoot()
{
	FVector SpawnLocation = RootComponent->GetSocketLocation("BulletSpawn");
	FVector Target = GetTarget();
	switch (AmmoContainer->ActiveAmmoType)
	{
		default:
			for (int i = 0; i < PelletCount; i++)
			{
				AProjectile* Projectile = SpawnProjectile(SpawnLocation, Target);
			}
			break;
		case EAmmoType::Type::B:
			break;
	}
	GiveShotFeedBack();
	SetLastShotTime();
	OnUse();
}