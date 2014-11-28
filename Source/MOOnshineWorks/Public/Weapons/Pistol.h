// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MOOnshineWorksGameMode.h"
#include "BlueprintLoader.h"
#include "Gun.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API APistol : public AGun
{
	GENERATED_UCLASS_BODY()

	virtual void Use() override;
	virtual void MagazineCountDecrement() override;
	virtual bool HasAmmo() override;
	virtual void Shoot() override;

protected:
	virtual void ReceiveBeginPlay() override;
	
};
