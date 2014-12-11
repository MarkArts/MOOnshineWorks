// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AmmoBarrel.h"


AAmmoBarrel::AAmmoBarrel(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PickupMesh->SetSimulatePhysics(false);
	BaseCollisionComponent->SetCollisionProfileName("BlockAll");
	PickupMesh->SetCollisionProfileName("BlockAll");
}


void AAmmoBarrel::OnPickedUp_Implementation(AMOOnshineWorksCharacter* Actor)
{
	int32 NewCount = FMath::Max(AmmoAmount - Actor->AmmoContainer->AmmoCounters[AmmoType], 0);
	Actor->AmmoContainer->AddAmmo(AmmoType, NewCount);
}