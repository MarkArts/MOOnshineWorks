﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_PegControllerDark.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"
#include "AI_PegEnemyDark.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_BasicEnemy.h"

AAI_PegControllerDark::AAI_PegControllerDark(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		static ConstructorHelpers::FClassFinder<AAI_PegEnemyDark> PlayerPawnBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AI_PegEnemyDark")); 
		if (PlayerPawnBPClass.Class != NULL)
		{
			EnemyClass = PlayerPawnBPClass.Class;
		}
	}
}

void AAI_PegControllerDark::AttackPlayer()
{
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	//AAI_BasicEnemy* WalkingEnemyzz = (AAI_BasicEnemy*)GetPawn();

	if(AiChar)
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
void AAI_PegControllerDark::SpeedUp()
{
	AAI_BasicEnemy* WalkingEnemy = (AAI_BasicEnemy*)GetPawn();
	WalkingEnemy->StartSprint();
}
void AAI_PegControllerDark::PegPatrol()
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
void AAI_PegControllerDark::PegGoActive()
{
	UBehaviorTree * BehaviorTree = NULL;
	AAI_PegEnemyDark* AiSpecific = Cast<AAI_PegEnemyDark>(GetPawn());
	FVector SpawnLocation = AiSpecific->GetActorLocation();
	FRotator SpawnRotation = AiSpecific->GetActorRotation();
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	UWorld* const World = GetWorld();

	//Nieuwe BlueprintEnemy Spawnen!
	AAI_BasicEnemy* NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(EnemyClass, SpawnLocation, SpawnRotation);
	AiSpecific->Destroy();

	if (NewPawn != NULL)
	{
		if (NewPawn->Controller == NULL)
		{
			NewPawn->SpawnDefaultController();
		}
		if (BehaviorTree != NULL)
		{
			AAIController* AIController = Cast<AAIController>(NewPawn->Controller);
			if (AIController != NULL)
			{
				AIController->RunBehaviorTree(BehaviorTree);
			}
		}
	}

	if (World)
	{
		World->SpawnActor<AActor>(AiChar->DeathBlueprint, RootComponent->GetComponentLocation(), RootComponent->GetComponentRotation());
	}

	//Laat AI speler direct aanvallen!
	AAI_BasicController* BasicController = (AAI_BasicController*)NewPawn->GetController();
	BasicController->FoundPlayer();
	BasicController->AISetAttackState();
}
