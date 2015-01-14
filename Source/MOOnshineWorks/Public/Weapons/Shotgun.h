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
	GENERATED_BODY()
public:
	AShotgun(const class FObjectInitializer& PCIP);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun)
	float PelletCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Charge)
	float ChargeMovementMultiplier;

	virtual void Use() override;
	virtual void Shoot() override;
	virtual bool CanCharge() override;
	virtual void StartCharge() override;
	virtual void EndCharge() override;
};