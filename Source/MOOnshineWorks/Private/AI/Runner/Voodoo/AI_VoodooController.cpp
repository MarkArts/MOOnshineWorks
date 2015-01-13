// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_VoodooController.h"
#include "AI_VoodooEnemy.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_BasicEnemy.h"

AAI_VoodooController::AAI_VoodooController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		static ConstructorHelpers::FClassFinder<AAI_VoodooEnemy> PlayerPawnBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIVoodoo"));
		if (PlayerPawnBPClass.Class != NULL)
		{
			EnemyClass = PlayerPawnBPClass.Class;
		}
	}
}
//void AAI_VoodooController::RunAway()
//{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Voodoo: RunAway functie");
//}
void AAI_VoodooController::ReduceTimer()
{
	AAI_VoodooEnemy* AiChar = Cast<AAI_VoodooEnemy>(GetPawn());
	float RemainingTime = AiChar->TimerActive - 1;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Voodoo: ReduceTimer functie aangeroepen");

	if (RemainingTime <= 0)
	{
		TimeIsUp();
	}
	else
	{
		AiChar->TimerActive = RemainingTime;
	}
}
void AAI_VoodooController::GoActive()
{
	UBehaviorTree * BehaviorTree = NULL;
	AAI_VoodooEnemy* AiSpecific = Cast<AAI_VoodooEnemy>(GetPawn());
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
}