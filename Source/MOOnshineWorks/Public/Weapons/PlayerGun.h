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

	FVector CharacterEquipOffset;
	FRotator CharacterEquipRotation;
	UPROPERTY(EditDefaultsOnly, Category = CameraShake)
	TSubclassOf<UCameraShake> ShotFeedBack;
	void GiveShotFeedBack();
	AAmmoContainer* AmmoContainer;

	virtual FVector GetTarget() override;	
	void UseAmmo();
	bool HasAmmo();
	virtual	TSubclassOf<class AProjectile> GetProjectileClass() override;
	void SetActiveGun();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TArray<TEnumAsByte<EAmmoType::Type>> AmmoTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TArray<int32> Multipliers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TArray<TSubclassOf<class AProjectile>> ProjectileClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 ActiveIndex;
	void SetActiveIndex(EAmmoType::Type);
	EAmmoType::Type FindActiveAmmoType();
	int32 FindActiveMultiplier();
	TSubclassOf<class AProjectile> FindActiveProjectileClass();
};