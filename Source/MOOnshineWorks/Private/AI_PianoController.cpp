// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_BasicEnemy.h"
#include "AI_PianoController.h"
#include "AI_PianoEnemy.h"


AAI_PianoController::AAI_PianoController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{ 
		static ConstructorHelpers::FClassFinder<AAI_PianoEnemy> PlayerPawnBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIPiano"));
		if (PlayerPawnBPClass.Class != NULL)
		{
			EnemyClass = PlayerPawnBPClass.Class;
		}
	}
}
void AAI_PianoController::AttackPlayer()
{
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	//AAI_BasicEnemy* WalkingEnemyzz = (AAI_BasicEnemy*)GetPawn();

	if (AiChar)
	{
		AAI_PianoEnemy* AiSpecific = Cast<AAI_PianoEnemy>(GetPawn());
		AMOOnshineWorksCharacter* playerCharacter = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		//AMOOnshineWorksCharacter* playerCharacter = Cast<AMOOnshineWorksCharacter>(*It);
		if (playerCharacter)
		{
			FVector PlayerLocation = playerCharacter->GetActorLocation();
			playerCharacter->DealDamage(AiChar->Damage);

			FRotator EnemyRotation = AiSpecific->GetActorRotation();
			//if (EnemyRotation.UnrotateVector(PlayerLocation).X < EnemyRotation.UnrotateVector(PlayerLocation).X)
			//{
				//nog niet af!!!
				playerCharacter->LaunchCharacter(AiSpecific->PianoPushBack, true, false);
			//}
		}
	}
}
void AAI_PianoController::SpeedUp()
{

}
void AAI_PianoController::PianoPatrol()
{
	
}
void AAI_PianoController::PianoGoActive()
{
	UBehaviorTree * BehaviorTree = NULL;
	AAI_PianoEnemy* AiSpecific = Cast<AAI_PianoEnemy>(GetPawn());
	FVector SpawnLocation = AiSpecific->GetActorLocation();
	FRotator SpawnRotation = AiSpecific->GetActorRotation();
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	UWorld* const World = GetWorld();
	float FloatEnemyDistanceShouldAttack = AiChar->EnemyDistanceShouldAttack;

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

	//De EnemyDistanceShouldAttack setten
	NewPawn->EnemyDistanceShouldAttack = FloatEnemyDistanceShouldAttack;

	//Laat AI speler direct aanvallen!
	AAI_BasicController* BasicController = (AAI_BasicController*)NewPawn->GetController();
	BasicController->FoundPlayer();
	BasicController->AISetAttackState();
}

