// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AmmoContainer.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Category = Ammo)
namespace EAmmoType
{
	enum Type
	{
		A = 0,
		B = 1,
		C = 2
	};
}

UCLASS()
class MOONSHINEWORKS_API AAmmoContainer : public AActor
{
	GENERATED_UCLASS_BODY()

public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TArray<int16> AmmoCounters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TEnumAsByte<EAmmoType::Type> ActiveAmmoType;

	void UseAmmo(int16 Count, EAmmoType::Type Type);
	bool HasAmmo(int16 Count, EAmmoType::Type Type);
	void SetAmmo(EAmmoType::Type Type, int16 NewCount);
};