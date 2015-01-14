// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "BatteryPickup.h"


ABatteryPickup::ABatteryPickup(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	LightPercentage = 20.f;
}


void ABatteryPickup::Collect(AActor* Target)
{
	AMOOnshineWorksCharacter* Actor = Cast<AMOOnshineWorksCharacter>(Target);
	Actor->SetLightPercentage(Actor->GetLightPercentage() + (LightPercentage / 100.f));
	Destroy();
}

