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
	FAmmoItem Item = FindActiveAmmoItem();
	return AmmoContainer->HasAmmo(Item.Multiplier, Item.Type);
}

void APlayerGun::UseAmmo()
{
	FAmmoItem Item = FindActiveAmmoItem();
	AmmoContainer->UseAmmo(Item.Multiplier, Item.Type);
}

TSubclassOf<class AProjectile> APlayerGun::GetProjectileClass()
{
	return FindActiveAmmoItem().ProjectileClass;
}

AmmoItem APlayerGun::FindActiveAmmoItem()
{
	for (FAmmoItem Item : AmmoItems)
	{
		if (Item.Type == AmmoContainer->ActiveAmmo)
		{
			return Item;
		}
	}
	AmmoContainer->SwitchGun(this);
	return FindActiveAmmoItem();
}

void APlayerGun::SwitchGun()
{
	AmmoContainer->ActiveAmmoType = AmmoItems[0].Type;
}