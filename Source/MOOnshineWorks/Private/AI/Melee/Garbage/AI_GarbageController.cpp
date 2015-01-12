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
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		static ConstructorHelpers::FClassFinder<AAI_GarbageEnemy> PlayerPawnBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIGarbage"));
		if (PlayerPawnBPClass.Class != NULL)
		{
			EnemyClass = PlayerPawnBPClass.Class;
		}
	}
}

void AAI_GarbageController::AttackPlayer()
{
	Super::AttackPlayer();
}
void AAI_GarbageController::Patrol()
{
	Super::Patrol();
}
void AAI_GarbageController::GoActive()
{
	UBehaviorTree * BehaviorTree = NULL;
	AAI_GarbageEnemy* AiSpecific = Cast<AAI_GarbageEnemy>(GetPawn());
	FVector SpawnLocation = AiSpecific->GetActorLocation();
	FRotator SpawnRotation = AiSpecific->GetActorRotation();
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	UWorld* const World = GetWorld();
	float FloatEnemyDistanceShouldAttack = AiChar->EnemyDistanceShouldAttack;
	bool ShouldAIPatrol = AiChar->AIPatrol;

	//Nieuwe BlueprintEnemy Spawnen!
	AAI_BasicEnemy* NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(EnemyClass, SpawnLocation, SpawnRotation);

	//Oude enemy destroyen
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

	//De AIPatrol zetten
	NewPawn->AIPatrol = ShouldAIPatrol;
	//De EnemyDistanceShouldAttack setten
	NewPawn->EnemyDistanceShouldAttack = FloatEnemyDistanceShouldAttack;

	//Laat AI speler direct aanvallen!
	AAI_BasicController* BasicController = (AAI_BasicController*)NewPawn->GetController();
	//BasicController->FoundPlayer();
	//BasicController->AISetAttackState();
}



