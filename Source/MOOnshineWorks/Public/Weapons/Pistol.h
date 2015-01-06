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
	GENERATED_UCLASS_BODY()

	virtual void Use() override;
	virtual bool CanCharge() override;
};
