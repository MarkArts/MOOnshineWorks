// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_Ghost.h"
#include "AI_GhostController.h"


AAI_Ghost::AAI_Ghost(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_GhostController::StaticClass();
}
