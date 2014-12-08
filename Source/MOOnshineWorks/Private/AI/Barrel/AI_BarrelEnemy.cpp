// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BarrelEnemy.h"


AAI_BarrelEnemy::AAI_BarrelEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    AIControllerClass = AAI_BarrelController::StaticClass();
    
    //LightType = EnemyLightType::Light;
}


