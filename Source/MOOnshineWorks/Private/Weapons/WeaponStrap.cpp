// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "WeaponStrap.h"


AWeaponStrap::AWeaponStrap(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AWeaponStrap::AddGun(APlayerGun* NewGun)
{
	Guns.Add(NewGun);
	if (Guns.Num() == 1)
	{
		ActiveGunIndex = 0;
	}
	else
	{
		NewGun->GunMesh->SetVisibility(false);
	}
}

void AWeaponStrap::NextGun()
{
	Guns[ActiveGunIndex]->GunMesh->SetVisibility(false);
	ActiveGunIndex = (ActiveGunIndex + 1) % Guns.Num();
	Guns[ActiveGunIndex]->GunMesh->SetVisibility(true);
}

void AWeaponStrap::PreviousGun()
{
	Guns[ActiveGunIndex]->GunMesh->SetVisibility(false);
	ActiveGunIndex = ((ActiveGunIndex - 1) + Guns.Num()) % Guns.Num();
	Guns[ActiveGunIndex]->GunMesh->SetVisibility(true);
}

APlayerGun* AWeaponStrap::GetActiveGun()
{
	return Guns[ActiveGunIndex];
}

bool AWeaponStrap::ContainsGun(APlayerGun* Gun)
{
	bool Result = false;
	for (int8 I = 0; I < Guns.Num(); I++)
	{
		if (Gun->GetClass() == Guns[I]->GetClass())
		{
			Result = true;
			break;
		}
	}
	return Result;
}