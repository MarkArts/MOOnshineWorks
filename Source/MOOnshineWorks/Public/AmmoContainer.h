// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AmmoContainer.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAmmoContainer : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TArray<int16> AmmoCounters;
};

enum EAmmoType {
	A = 0,
	B = 1,
	C = 2
};
