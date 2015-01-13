// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Collectible.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ABatteryPickup : public ACollectible
{
	GENERATED_BODY()
public:
	ABatteryPickup(const class FObjectInitializer& PCIP);

	//The mana this chest contains
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	float LightPercentage;

	//Override the OnPickedUp function (use implementation because this is a BlueprintNativeEvent)
	virtual void Collect(AActor* Target) override;
	
};
