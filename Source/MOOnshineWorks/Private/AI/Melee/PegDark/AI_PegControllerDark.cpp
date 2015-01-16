// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_PegControllerDark.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"
#include "AI_PegEnemyDark.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_BasicEnemy.h"

AAI_PegControllerDark::AAI_PegControllerDark(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}
void AAI_PegControllerDark::AttackPlayer()
{
	Super::AttackPlayer();
}
void AAI_PegControllerDark::Patrol()
{
	Super::Patrol();
}
