// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Gun.h"
#include "AIBookGun.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAIBookGun : public AGun
{
	GENERATED_UCLASS_BODY()

	virtual void Use() override;
	virtual void Shoot() override;
};
