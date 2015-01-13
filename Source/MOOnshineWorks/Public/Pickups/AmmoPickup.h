// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AmmoContainer.h"
#include "MOOnshineWorksCharacter.h"
#include "Collectible.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAmmoPickup : public ACollectible
{
	GENERATED_BODY()
public:
	AAmmoPickup(const class FObjectInitializer& PCIP);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TEnumAsByte<EAmmoType::Type> AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 AmmoAmount;
	
	virtual void Collect(AActor* Target) override;
};
