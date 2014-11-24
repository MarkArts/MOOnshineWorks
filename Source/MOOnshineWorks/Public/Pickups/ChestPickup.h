// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "ChestPickup.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AChestPickup : public APickup
{
	GENERATED_UCLASS_BODY()

	//The mana this chest contains
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	float valueMana;

	//Override the OnPickedUp function (use implementation because this is a BlueprintNativeEvent)
	void OnPickedUp_Implementation(AMOOnshineWorksCharacter *Actor) override;
};
