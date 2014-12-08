// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "PlayerGun.h"


APlayerGun::APlayerGun(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}


FVector APlayerGun::GetTarget()
{
	return GetPlayerTarget();
}

bool APlayerGun::HasAmmo()
{
	return AmmoContainer->HasAmmo(FindActiveMultiplier(), FindActiveAmmoType());
}

void APlayerGun::UseAmmo()
{
	AmmoContainer->UseAmmo(FindActiveMultiplier(), FindActiveAmmoType());
}

TSubclassOf<class AProjectile> APlayerGun::GetProjectileClass()
{
	return FindActiveProjectileClass();
}

void APlayerGun::SetActiveIndex(EAmmoType::Type NewType)
{
	bool IsSet = false;
	for (int8 I = 0; I < AmmoTypes.Num(); I++)
	{
		if (AmmoTypes[I] == NewType)
		{
			ActiveIndex = I;
			AmmoContainer->ActiveAmmoType = AmmoTypes[I];
			IsSet = true;
			break;
		}
	}
	if (!IsSet)
	{
		SetActiveGun();
	}
}

EAmmoType::Type APlayerGun::FindActiveAmmoType()
{
	return AmmoTypes[ActiveIndex];
}

int8 APlayerGun::FindActiveMultiplier()
{
	return Multipliers[ActiveIndex];
}

TSubclassOf<class AProjectile> APlayerGun::FindActiveProjectileClass()
{
	return ProjectileClasses[ActiveIndex];
}

void APlayerGun::SetActiveGun()
{
	AmmoContainer->ActiveAmmoType = AmmoTypes[0];
	ActiveIndex = 0;
}