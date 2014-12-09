// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickups/AmmoPickup.h"
#include "AmmoBarrel.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAmmoBarrel : public AAmmoPickup
{
	GENERATED_UCLASS_BODY()

	void OnPickedUp_Implementation(AMOOnshineWorksCharacter *Actor) override;
	
};
