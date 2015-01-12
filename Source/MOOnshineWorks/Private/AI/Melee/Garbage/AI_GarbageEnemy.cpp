// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_GarbageEnemy.h"
#include "AI_GarbageController.h"

AAI_GarbageEnemy::AAI_GarbageEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_GarbageController::StaticClass();
}


