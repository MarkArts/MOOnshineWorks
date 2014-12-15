// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AmmoPickup.h"


AAmmoPickup::AAmmoPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


void AAmmoPickup::Collect(AActor* Target)
{
	AMOOnshineWorksCharacter* Actor = Cast<AMOOnshineWorksCharacter>(Target);
	Actor->AmmoContainer->AddAmmo(AmmoType, AmmoAmount);
	Destroy();
}
