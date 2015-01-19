// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "InteractableGun.h"


AInteractableGun::AInteractableGun(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AmmoGivenIfHasGun = 5;
}

void AInteractableGun::OnInteract_Implementation(AActor* Target)
{
	AMOOnshineWorksCharacter* CharTarget = Cast<AMOOnshineWorksCharacter>(Target);
	if (CharTarget)
	{
		APlayerGun* NewGun = GetWorld()->SpawnActor<APlayerGun>(Gun);
		if (!CharTarget->WeaponStrap->ContainsGun(Gun) && NewGun)
		{
			CharTarget->EquipGun(NewGun);
		}
		else if (CharTarget->WeaponStrap->ContainsGun(Gun) && NewGun)
		{
			CharTarget->AmmoContainer->AddAmmo(NewGun->AmmoTypes[NewGun->ActiveIndex], AmmoGivenIfHasGun);
			NewGun->Destroy();
		}
	}
	Destroy();
}
