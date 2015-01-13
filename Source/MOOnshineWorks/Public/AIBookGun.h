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
	GENERATED_BODY()
public:
	AAIBookGun(const class FObjectInitializer& PCIP);

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = AIGun)
	USphereComponent* GunSphere;

	virtual void Use() override;
	virtual void Shoot() override;
	virtual FVector GetTarget() override;
};
