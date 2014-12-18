// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/PlayerGun.h"
#include "Bazooka.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ABazooka : public APlayerGun
{
	GENERATED_UCLASS_BODY()

	virtual void Use() override;
	virtual void Shoot() override;
};
