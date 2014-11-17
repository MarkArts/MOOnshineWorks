// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicEnemy.h"


AAI_BasicEnemy::AAI_BasicEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
<<<<<<< HEAD
	AIControllerClass = AAI_BasicEnemy::StaticClass();
	CharacterMovement->AirControl = 0.2f;
=======
	Health = 0.f;
	Defense = 0.f;
	Speed = 0.f;
>>>>>>> origin/AI-Patrol
}

void AAI_BasicEnemy::StartSprint()
{
	CharacterMovement->MaxWalkSpeed = 500;
}

void AAI_BasicEnemy::StartWalk()
{
	CharacterMovement->MaxWalkSpeed = 100;
}
void AAI_BasicEnemy::ChangeLightDark(bool CurrentDarkLight)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Switch Stance nu!"));
}


