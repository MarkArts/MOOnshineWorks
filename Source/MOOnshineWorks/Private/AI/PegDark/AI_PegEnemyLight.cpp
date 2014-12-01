// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_PegEnemyLight.h"
#include "AI_PegControllerLight.h"


AAI_PegEnemyLight::AAI_PegEnemyLight(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_PegControllerLight::StaticClass();

	LightType = EnemyLightType::Light;
}
