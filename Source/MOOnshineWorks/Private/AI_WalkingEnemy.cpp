// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_WalkingEnemy.h"


AAI_WalkingEnemy::AAI_WalkingEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


void AAI_WalkingEnemy::StartSprint()
{
	CharacterMovement->MaxWalkSpeed = 500;
}

void AAI_WalkingEnemy::StartWalk()
{
	CharacterMovement->MaxWalkSpeed = 100;
}