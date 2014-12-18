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
	if (Actor->AmmoContainer->GetAmmo(AmmoType) < 20)
	{
		if (Actor->AmmoContainer->GetAmmo(AmmoType) + AmmoAmount > 20)
		{
			while (Actor->AmmoContainer->GetAmmo(AmmoType) < 20 && AmmoAmount > 0)
			{
				Actor->AmmoContainer->AddAmmo(AmmoType, 1);
				AmmoAmount--;
			}
			if (AmmoAmount < 1)
			{
				Destroy();
			}
		}
		else
		{
			Actor->AmmoContainer->AddAmmo(AmmoType, AmmoAmount);
			Destroy();
		}
	}
}
