// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AmmoContainer.h"


AAmmoContainer::AAmmoContainer(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AmmoCounters.Add(15);
	AmmoCounters.Add(0);
	AmmoCounters.Add(0);
	ActiveAmmoType = EAmmoType::Type::A;
}

void AAmmoContainer::UseAmmo(int16 Count, EAmmoType::Type Type)
{
	if (HasAmmo(Count, Type))
	{
		SetAmmo(Type, AmmoCounters[Type] - Count);
	}
}

bool AAmmoContainer::HasAmmo(int16 Count, EAmmoType::Type Type)
{
	return AmmoCounters[Type] >= Count;
}

void AAmmoContainer::SetAmmo(EAmmoType::Type Type, int16 NewCount)
{
	AmmoCounters[Type] = NewCount;
}

