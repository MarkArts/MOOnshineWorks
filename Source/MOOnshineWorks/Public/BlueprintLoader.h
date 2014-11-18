// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Projectile.h"
#include "AI_BarrelEnemy.h"
//#include "BlueprintLoader.generated.h"
/**
 * 
 */
class MOONSHINEWORKS_API BlueprintLoader
{
public:
	TSubclassOf<class AProjectile> ProjectileClass;
	TSubclassOf<class AAI_BarrelEnemy> AI_BarrelEnemy;
	TSubclassOf<class APawn> MOOnshineWorksCharacter;

	BlueprintLoader();
	~BlueprintLoader();
};
