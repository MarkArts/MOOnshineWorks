// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickups/Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ABatteryPickup : public APickup
{
	GENERATED_UCLASS_BODY()

	//The mana this chest contains
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	float LightPercentage;

	//Override the OnPickedUp function (use implementation because this is a BlueprintNativeEvent)
	void OnPickedUp_Implementation(AMOOnshineWorksCharacter *Actor) override;
	
};
