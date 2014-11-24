// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BookEnemyLight.h"
#include "AI_BookControllerLight.h"


AAI_BookEnemyLight::AAI_BookEnemyLight(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_BookControllerLight::StaticClass();

	Health = 3.f;
	Defense = 0.f;
	Speed = 1.2f;

	LightType = EnemyLightType::Light;
}


