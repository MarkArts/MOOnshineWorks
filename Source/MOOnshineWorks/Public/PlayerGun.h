// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AmmoContainer.h"
#include "Weapons/Gun.h"
#include "PlayerGun.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API APlayerGun : public AGun
{
	GENERATED_UCLASS_BODY()

	AAmmoContainer* AmmoContainer;

	USTRUCT(BlueprintType)
	struct FAmmoItem
	{
		GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = AmmoItem)
		EAmmoType Type;

		UPROPERTY(EditAnywhere, Category = AmmoItem)
		int8 Multiplier;

		UPROPERTY(EditAnywhere, Category = AmmoItem)
		TSubclassOf<class AProjectile> ProjectileClass;
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TArray<FAmmoItem> AmmoItems;

	virtual FVector GetTarget() override;	
	void UseAmmo();
	bool HasAmmo();
	virtual	TSubclassOf<class AProjectile> GetProjectileClass() override;
	FAmmoItem FindActiveAmmoItem();
	void SetActiveGun();
};
