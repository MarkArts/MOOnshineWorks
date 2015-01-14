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
	GENERATED_BODY()
public:
	AAmmoBarrel(const class FObjectInitializer& PCIP);

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	//TSubobjectPtr<UStaticMeshComponent> Mesh;

	virtual void Collect(AActor* Target) override;
	
};
