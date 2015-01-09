// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_PegControllerDark.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"
#include "AI_PegEnemyDark.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_BasicEnemy.h"

AAI_MeleeController::AAI_MeleeController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

void AAI_MeleeController::AttackPlayer()
{
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	//AAI_BasicEnemy* WalkingEnemyzz = (AAI_BasicEnemy*)GetPawn();

	if (AiChar)
	{
		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			AMOOnshineWorksCharacter* playerCharacter = Cast<AMOOnshineWorksCharacter>(*It);
			if (playerCharacter)
			{
				playerCharacter->DealDamage(AiChar->Damage);
			}
		}
	}
}
void AAI_MeleeController::Patrol()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}

	AAI_BasicEnemy* BaseEnemy = (AAI_BasicEnemy*)GetPawn();
	BaseEnemy->StartWalk();

	FVector MyLoc = MyBot->GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(MyLoc[0]));

	float random = (float)rand() / (float)RAND_MAX;
	float randomy = (float)rand() / (float)RAND_MAX;

	int xValue = 1 + random * ((3) - (1));
	int yValue = 1 + randomy * ((3) - (1));

	float x, y;

	if (xValue == 1)
		x = ((MyLoc[0]) + 100) + random * (((MyLoc[0]) + 400) - ((MyLoc[0]) + 100));
	else
		x = ((MyLoc[0]) - 100) + random * (((MyLoc[0]) - 400) - ((MyLoc[0]) - 100));
	if (yValue == 1)
		y = ((MyLoc[1]) + 100) + random * (((MyLoc[1]) + 400) - ((MyLoc[1]) + 100));
	else
		y = ((MyLoc[1]) - 100) + random * (((MyLoc[1]) - 400) - ((MyLoc[1]) - 100));

	MyLoc.Set(x, y, MyLoc[2]);
	BlackboardComp->SetValueAsVector(SetPatrolRoute, MyLoc);
}
void AAI_MeleeController::GoActive()
{
	//override
}