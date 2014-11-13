// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Pistol.h"


APistol::APistol(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	name = "Pistol";
	id = 14.f;

	magazineCapacity = 15.f;
	magazineLoadCount = magazineCapacity;
	damageValue = 5.f;
	reloadTime = 2.f;
	spreadAngle = 45.f;
	reloading = false;
}


