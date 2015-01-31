// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Pistol.h"


APistol::APistol(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	Name = "Plungebow";
	Type = EGunType::Crossbow;
	Id = 14.f;

	CharacterEquipOffset = FVector(20.f, 40.f, -40.f);
	CharacterEquipRotation = FRotator(0.f, 80.f, 0.f);

	SpreadAngle = 0.f;
	ShootCooldown = 0.8f;

	Charge = 0.f;
	IsCharging = false;
	ChargeRatePerSecond = 0.5f;
	ChargeMultiplier = 3.f;
	ChanceToDestroyAmmoOnChargedShot = 0.25f;
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
	if (Projectile && CanCharge())
	{
		if (Charge == 1.f)
		{
			float ChargeEffectMultiplier = (Charge * ChargeMultiplier);
			Projectile->DamageValue *= ChargeEffectMultiplier;
			Projectile->ProjectileMovement->Velocity = Projectile->GetVelocity() * ChargeEffectMultiplier;
			float Random = FMath::FRandRange(0.f, 1.f);
			if (Random < ChanceToDestroyAmmoOnChargedShot)
			{
				Projectile->DeathBlueprint = nullptr;
			}
		}
	}
	Super::Shoot();
}

bool APistol::CanCharge()
{
	return true && HasAmmo() && CanShoot();
}