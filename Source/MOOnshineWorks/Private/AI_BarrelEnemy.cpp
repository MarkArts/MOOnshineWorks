// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BarrelEnemy.h"
#include "AI_BarrelController.h"


AAI_BarrelEnemy::AAI_BarrelEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_BarrelController::StaticClass();
<<<<<<< HEAD
//	static ConstructorHelpers::FClassFinder<UBehaviorTree> tree(TEXT("/Game/Blueprints/AIBlueprints/BarrelEnemy/Services/BarrelBrainTree"));
//	Behavior = tree.Class.GetDefaultObject();
=======

	Health = 5.f;
	Defense = 0.f;
	Speed = 0.6f;
>>>>>>> origin/AI-Patrol
}
