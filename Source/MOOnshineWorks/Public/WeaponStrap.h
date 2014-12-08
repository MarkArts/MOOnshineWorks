// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerGun.h"
#include "GameFramework/Actor.h"
#include "WeaponStrap.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AWeaponStrap : public AActor
{
	GENERATED_UCLASS_BODY()

	TArray<APlayerGun*> Guns;
	int8 ActiveGunIndex;

	void AddGun(APlayerGun* NewGun);
	void NextGun();
	void PreviousGun();
	APlayerGun* GetActiveGun();
};
