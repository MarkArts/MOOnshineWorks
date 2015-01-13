// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_VoodooEnemy.h"
#include "AI_VoodooController.h"


AAI_VoodooEnemy::AAI_VoodooEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_VoodooController::StaticClass();

	TimerActive = 0;
}


