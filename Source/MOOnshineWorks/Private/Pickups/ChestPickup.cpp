// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "ChestPickup.h"


AChestPickup::AChestPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//The baseValue mana in the chest
	valueMana = 50.f;
}

void AChestPickup::OnPickedUp_Implementation(AMOOnshineWorksCharacter *Actor)
{
	//Call the parent implementation of OnPickedUp first.
	Super::OnPickedUp_Implementation(Actor);

	Actor->SetStamina(Actor->GetStamina() + 20.f);

	//Destroy the chest
	Destroy();
}


