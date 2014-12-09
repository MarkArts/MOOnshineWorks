// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Projectile.h"
#include "AIProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAIProjectile : public AProjectile
{
	GENERATED_UCLASS_BODY()

	virtual void HitActor(AActor* OtherActor) override;
	
};