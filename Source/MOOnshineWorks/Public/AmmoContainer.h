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

	UENUM(BlueprintType, Category = Ammo)
	enum class EAmmoType : uint8
	{
		A = 0,
		B = 1,
		C = 2
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TArray<int16> AmmoCounters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	EAmmoType ActiveAmmoType;

	void UseAmmo(int16 Count, EAmmoType Type);
	bool HasAmmo(int16 Count, EAmmoType Type);
	void SetAmmo(EAmmoType Type, int16 NewCount);
};

