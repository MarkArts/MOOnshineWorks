// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "BatteryPickup.h"


ABatteryPickup::ABatteryPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	LightPercentage = 20.f;
}


void ABatteryPickup::OnPickedUp_Implementation(AMOOnshineWorksCharacter* Actor)
{
	//Call the parent implementation of OnPickedUp first.
	Super::OnPickedUp_Implementation(Actor);

	Actor->SetLightPercentage(Actor->GetLightPercentage() + (LightPercentage / 100.f));

	//Destroy the chest
	Destroy();
}

