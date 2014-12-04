// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AmmoContainer.h"


AAmmoContainer::AAmmoContainer(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AmmoCounters.Add(0);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("Ammo A: "));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(AmmoCounters[EAmmoType::A]));
}


