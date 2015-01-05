// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BarrelController.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"
#include "AI_BarrelEnemy.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_BasicEnemy.h"


AAI_BarrelController::AAI_BarrelController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		static ConstructorHelpers::FClassFinder<AAI_BarrelEnemy> PlayerPawnBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AI_BarrelEnemy"));
		if (PlayerPawnBPClass.Class != NULL)
		{
			EnemyClass = PlayerPawnBPClass.Class;
		}
	}
}


void AAI_BarrelController::AttackPlayer()
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

void AAI_BarrelController::SpeedUp()
{
    AAI_BasicEnemy* WalkingEnemy = (AAI_BasicEnemy*)GetPawn();
    WalkingEnemy->StartSprint();
}

void AAI_BarrelController::BarrelPatrol()
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

/*
void AAI_BarrelController::BarrelGoActive()
{
	UBehaviorTree * BehaviorTree = NULL;
	AAI_BarrelEnemy* AiSpecific = Cast<AAI_BarrelEnemy>(GetPawn());
	FVector SpawnLocation = AiSpecific->GetActorLocation();
	FRotator SpawnRotation = AiSpecific->GetActorRotation();
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	UWorld* const World = GetWorld();
	float FloatEnemyDistanceShouldAttack = AiChar->EnemyDistanceShouldAttack;
	bool ShouldAIPatrol = AiChar->AIPatrol;

	//Nieuwe BlueprintEnemy Spawnen!
	APawn* NewPawn = GetWorld()->SpawnActor<APawn>(EnemyClass, SpawnLocation, SpawnRotation);
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
	//De AIPatrol zetten
	NewPawn->AIPatrol = ShouldAIPatrol;

	//Laat AI speler direct aanvallen!
	AAI_BasicController* BasicController = (AAI_BasicController*)NewPawn->GetController();
	BasicController->FoundPlayer();
	BasicController->AISetAttackState();
}
*/

void AAI_BarrelController::BarrelGoActive()
{
	UBehaviorTree * BehaviorTree = NULL;
	AAI_BarrelEnemy* AiSpecific = Cast<AAI_BarrelEnemy>(GetPawn());
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
	BasicController->FoundPlayer();
	BasicController->AISetAttackState();
}