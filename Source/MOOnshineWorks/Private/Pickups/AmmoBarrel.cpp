// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AmmoBarrel.h"


AAmmoBarrel::AAmmoBarrel(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	//Mesh->SetSimulatePhysics(false);
	//Mesh->SetCollisionProfileName("BlockAll");
}


void AAmmoBarrel::Collect(AActor* Target)
{
	AMOOnshineWorksCharacter* Actor = Cast<AMOOnshineWorksCharacter>(Target);
	int32 NewCount = FMath::Max(AmmoAmount - Actor->AmmoContainer->AmmoCounters[AmmoType], 0);
	Actor->AmmoContainer->AddAmmo(AmmoType, NewCount);
}