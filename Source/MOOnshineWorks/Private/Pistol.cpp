// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Pistol.h"


APistol::APistol(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	name = "Pistol";
	id = 14.f;

	static ConstructorHelpers::FClassFinder<AProjectile> random(TEXT("/Game/Blueprints/BP_Projectile"));
	projectileClass = random.Class;

	magazineCapacity = 15.f;
	magazineLoadCount = magazineCapacity;
	damageValue = 5.f;
	reloadTime = 2.f;
	spreadAngle = 0.f;
	reloading = false;
}


