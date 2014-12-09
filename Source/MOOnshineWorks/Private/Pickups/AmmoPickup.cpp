// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AmmoPickup.h"


AAmmoPickup::AAmmoPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


void AAmmoPickup::OnPickedUp_Implementation(AMOOnshineWorksCharacter* Actor)
{
	//Call the parent implementation of OnPickedUp first.
	Super::OnPickedUp_Implementation(Actor);

	Actor->AmmoContainer->AddAmmo(AmmoType, AmmoAmount);

	//Destroy the chest
	Destroy();
}
