// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_PianoEnemy.h"
#include "AI_PianoController.h"

AAI_PianoEnemy::AAI_PianoEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_PianoController::StaticClass();

	LightType = EnemyLightType::Light;

	PianoPushPower = 0;
}


