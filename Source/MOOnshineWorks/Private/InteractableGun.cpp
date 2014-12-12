// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "InteractableGun.h"


AInteractableGun::AInteractableGun(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}

void AInteractableGun::OnInteract_Implementation(AActor* Target)
{
	AMOOnshineWorksCharacter* CharTarget = Cast<AMOOnshineWorksCharacter>(Target);
	if (CharTarget && !CharTarget->WeaponStrap->ContainsGun(Gun))
	{
		APlayerGun* NewGun = GetWorld()->SpawnActor<APlayerGun>(Gun);
		if (NewGun)
		{
			CharTarget->EquipGun(NewGun);
		}
	}
	Destroy();
}
