// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_FridgeEnemy.h"
#include "AI_FridgeController.h"


AAI_FridgeEnemy::AAI_FridgeEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_FridgeController::StaticClass();
}


