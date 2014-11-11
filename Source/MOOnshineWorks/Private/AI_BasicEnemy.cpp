// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicEnemy.h"


AAI_BasicEnemy::AAI_BasicEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//AIControllerClass = AAI_BasicEnemy::StaticClass();
}

void AAI_BasicEnemy::StartSprint()
{
	CharacterMovement->MaxWalkSpeed = 500;
}

void AAI_BasicEnemy::StartWalk()
{
	CharacterMovement->MaxWalkSpeed = 100;
}

