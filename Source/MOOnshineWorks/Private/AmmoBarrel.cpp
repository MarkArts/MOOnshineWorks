// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AmmoBarrel.h"


AAmmoBarrel::AAmmoBarrel(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


void AAmmoBarrel::OnPickedUp_Implementation(AMOOnshineWorksCharacter* Actor)
{
	//Call the parent implementation of OnPickedUp first.
	Super::OnPickedUp_Implementation(Actor);
	int16 NewCount = FMath::Max(AmmoAmount - Actor->AmmoContainer->GetAmmo(AmmoType), 0);
	Actor->AmmoContainer->AddAmmo(AmmoType, AmmoAmount);
}