// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_PegEnemyDark.h"
#include "AI_PegControllerDark.h"


AAI_PegEnemyDark::AAI_PegEnemyDark(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_PegControllerDark::StaticClass();

	//LightType = EnemyLightType::Light;
}
