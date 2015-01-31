// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "ExplosiveProjectile.h"
#include "Bazooka.h"


ABazooka::ABazooka(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	Name = "Teazooka";
	Type = EGunType::Bazooka;
	Id = 16.f;

	CharacterEquipOffset = FVector(20.f, 17.5f, -40.f);
	CharacterEquipRotation = FRotator(0.f, 80.f, 0.f);

	SpreadAngle = 5.f;
	ShootCooldown = 2.f;

	Charge = 0.f;
	IsCharging = false;
	ChargeRatePerSecond = (1.f / 3.f);
	ChargeMultiplier = 3.f;
	ChargeMovementMultiplier = 0.5f;
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
	AExplosiveProjectile* Projectile = Cast<AExplosiveProjectile>(SpawnProjectile(SpawnLocation, Target));
	if (Projectile && CanCharge())
	{
		if (Charge == 1.f)
		{
			float ChargeEffectMultiplier = (Charge * ChargeMultiplier);
			Projectile->DamageValue *= ChargeEffectMultiplier;
			Projectile->ExplosionRadius *= ChargeEffectMultiplier;
			Projectile->DoesPushback = false;
			Projectile->DoesPushback = true;
		}
	}
	Super::Shoot();
}

bool ABazooka::CanCharge()
{
	return true && HasAmmo() && CanShoot();
}

void ABazooka::StartCharge()
{
	Super::StartCharge();
	AMOOnshineWorksCharacter* Owner = Cast<AMOOnshineWorksCharacter>(GetOwner());
	if (Owner)
	{
		Owner->GetCharacterMovement()->MaxWalkSpeed *= ChargeMovementMultiplier;
	}
}

void ABazooka::EndCharge()
{
	Super::EndCharge();
	AMOOnshineWorksCharacter* Owner = Cast<AMOOnshineWorksCharacter>(GetOwner());
	if (Owner)
	{
		Owner->GetCharacterMovement()->MaxWalkSpeed /= ChargeMovementMultiplier;
	}
}

void ABazooka::StopCharge()
{
	AMOOnshineWorksCharacter* Owner = Cast<AMOOnshineWorksCharacter>(GetOwner());
	if (Owner && IsCharging)
	{
		Owner->GetCharacterMovement()->MaxWalkSpeed /= ChargeMovementMultiplier;
	}
	Super::StopCharge();
}