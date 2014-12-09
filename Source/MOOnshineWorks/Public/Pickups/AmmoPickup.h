// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AmmoContainer.h"
#include "MOOnshineWorksCharacter.h"
#include "Pickups/Pickup.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAmmoPickup : public APickup
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TEnumAsByte<EAmmoType::Type> AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 AmmoAmount;
	
	void OnPickedUp_Implementation(AMOOnshineWorksCharacter *Actor) override;
};
