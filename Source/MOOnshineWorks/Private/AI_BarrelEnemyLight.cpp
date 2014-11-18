// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BarrelEnemyLight.h"
#include "AI_BarrelControllerLight.h"


AAI_BarrelEnemyLight::AAI_BarrelEnemyLight(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_BarrelControllerLight::StaticClass();

	Health = 5.f;
	Defense = 0.f;
	Speed = 0.6f;

	LightType = EnemyLightType::Light;
}
