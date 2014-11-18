// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_ClosetEnemyLight.h"
#include "AI_ClosetControllerLight.h"


AAI_ClosetEnemyLight::AAI_ClosetEnemyLight(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_ClosetControllerLight::StaticClass();

	Health = 5.f;
	Defense = 0.f;
	Speed = 0.6f;

	LightType = EnemyLightType::Light;
}
