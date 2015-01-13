// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MOOnshineWorksGameMode.h"
#include "BlueprintLoader.h"
#include "PlayerGun.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API APistol : public APlayerGun
{
	GENERATED_BODY()
public:
	APistol(const class FObjectInitializer& PCIP);

	virtual void Use() override;
	virtual void Shoot() override;
	virtual bool CanCharge() override;
};
