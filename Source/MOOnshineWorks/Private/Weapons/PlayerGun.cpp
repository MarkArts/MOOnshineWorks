// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "PlayerGun.h"


APlayerGun::APlayerGun(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}


FVector APlayerGun::GetTarget()
{
	return GetPlayerTarget();
}

void APlayerGun::Shoot()
{
	GiveShotFeedBack();
	SetLastShotTime();
	OnUse();
	SetLastShotTime();
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

int32 APlayerGun::FindActiveMultiplier()
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

void APlayerGun::GiveShotFeedBack()
{
	AMOOnshineWorksCharacter* Owner = Cast<AMOOnshineWorksCharacter>(GetOwner());
	Owner->StartShake(ShotFeedBack);
}

int32 APlayerGun::GetRemainingShotCount()
{
	int32 Result = AmmoContainer->GetAmmo(FindActiveAmmoType());
    Result = FPlatformMath::FloorToInt(Result / FindActiveMultiplier());
	//Result = FMath::Floor(Result / FindActiveMultiplier());
	return Result;
}

void APlayerGun::SetVisibility_Implementation(bool Visible)
{
	//GunMesh->SetVisibility(Visible);
}
