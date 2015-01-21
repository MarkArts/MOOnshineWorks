// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "AI_BookControllerLight.h"
#include "AI_BasicController.h"
#include "AI_BasicEnemy.h"
#include "AI_BookEnemyLight.h"
#include "BasicAnimationInstance.h"

AAI_BookControllerLight::AAI_BookControllerLight(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}
/*
void AAI_BookControllerLight::GoBackToOriginalPosition()
{
	Super::GoBackToOriginalPosition();
}
*/
void AAI_BookControllerLight::Patrol()
{
	Super::Patrol();
}

void AAI_BookControllerLight::AttackPlayer()
{
	//Op de speler gaan schieten
	AAI_BookEnemyLight* BaseEnemy = Cast<AAI_BookEnemyLight>(GetPawn());
	BaseEnemy->Gun->Use();
}
