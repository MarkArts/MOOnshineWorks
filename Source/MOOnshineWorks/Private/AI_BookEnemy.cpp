// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BookEnemy.h"


AAI_BookEnemy::AAI_BookEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_BasicController::StaticClass();
}


