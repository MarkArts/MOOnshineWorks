// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "InteractableGun.h"


AInteractableGun::AInteractableGun(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AmmoGivenIfHasGun = 5;
}

void AInteractableGun::Interact(AActor* Target)
{
	if (ShouldUseOnce)
	{
		if (!IsUsed){
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
					UsedText = FString(TEXT("Already have this weapon, picked up the ammo instead"));
					NewGun->Destroy();
				}
			}
			Destroy();
		}
	}

	Super::Interact(Target);
}
