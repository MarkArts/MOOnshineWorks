// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AmmoContainer.h"


AAmmoContainer::AAmmoContainer(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AmmoCounters.Add(10);
	AmmoCounters.Add(15);
	AmmoCounters.Add(5);
	AmmoCounters.Add(100);
	ActiveAmmoType = EAmmoType::Type::A;
	MaximumAmmoCount.Add(10);
	MaximumAmmoCount.Add(15);
	MaximumAmmoCount.Add(5);
	MaximumAmmoCount.Add(100);
}

int32 AAmmoContainer::AddAmmo(EAmmoType::Type AmmoType, int32 AmmoAmount)
{
	int32 Result = 0;
	if (MaximumAmmoCount[AmmoType] >= GetAmmo(AmmoType) + AmmoAmount)
	{
		SetAmmo(AmmoType, GetAmmo(AmmoType) + AmmoAmount);
	}
	else
	{
		Result = (GetAmmo(AmmoType) + AmmoAmount) - MaximumAmmoCount[AmmoType];
		SetAmmo(AmmoType, MaximumAmmoCount[AmmoType]);
	}
	return Result;
}

void AAmmoContainer::UseAmmo(int32 Count, EAmmoType::Type Type)
{
	if (HasAmmo(Count, Type))
	{
		SetAmmo(Type, AmmoCounters[Type] - Count);
	}
}

bool AAmmoContainer::HasAmmo(int32 Count, EAmmoType::Type Type)
{
	return AmmoCounters[Type] >= Count;
}

void AAmmoContainer::SetAmmo(EAmmoType::Type Type, int32 NewCount)
{
	AmmoCounters[Type] = NewCount;
}

int32 AAmmoContainer::GetActiveAmmo()
{
	return AmmoCounters[ActiveAmmoType];
}

int32 AAmmoContainer::GetAmmo(EAmmoType::Type Type)
{
	return AmmoCounters[Type];
}