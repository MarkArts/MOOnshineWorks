// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "ChestPickup.h"


AChestPickup::AChestPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//The baseValue mana in the chest
	valueMana = 50.f;
}

void AChestPickup::OnPickedUp_Implementation()
{
	//Call the parent implementation of OnPickedUp first.
	Super::OnPickedUp_Implementation();

	//Destroy the chest
	Destroy();
}


