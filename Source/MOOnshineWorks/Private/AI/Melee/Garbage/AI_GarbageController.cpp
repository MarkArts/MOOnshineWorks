// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_GarbageEnemy.h"
#include "AI_GarbageController.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_BasicEnemy.h"

AAI_GarbageController::AAI_GarbageController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}
void AAI_GarbageController::AttackPlayer()
{
	Super::AttackPlayer();
}
void AAI_GarbageController::Patrol()
{
	Super::Patrol();
}


