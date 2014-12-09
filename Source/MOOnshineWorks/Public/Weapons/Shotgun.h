// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MOOnshineWorksGameMode.h"
#include "BlueprintLoader.h"
#include "PlayerGun.h"
#include "Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AShotgun : public APlayerGun
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun)
	float PelletCount;

	virtual void Use() override;
	virtual void Shoot() override;

};