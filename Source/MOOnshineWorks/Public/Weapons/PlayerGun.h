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

	virtual FVector GetTarget() override;	
	void UseAmmo();
	bool HasAmmo();
	virtual	TSubclassOf<class AProjectile> GetProjectileClass() override;
	void SetActiveGun();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TArray<TEnumAsByte<EAmmoType::Type>> AmmoTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TArray<int8> Multipliers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TArray<TSubclassOf<class AProjectile>> ProjectileClasses;

	uint8 ActiveIndex;
	void SetActiveIndex(EAmmoType::Type);
	EAmmoType::Type FindActiveAmmoType();
	int8 FindActiveMultiplier();
	TSubclassOf<class AProjectile> FindActiveProjectileClass();
};