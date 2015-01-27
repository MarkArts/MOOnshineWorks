// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "AI_BasicController.h"
#include "AI_BasicEnemy.h"
#include "AI_RunnerEnemy.h"
#include "AI_RunnerController.h"


AAI_RunnerController::AAI_RunnerController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		static ConstructorHelpers::FClassFinder<AAI_VoodooEnemy> VoodooBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIVoodoo"));
		if (VoodooBPClass.Class != NULL)
		{
			VoodooEnemyClass = VoodooBPClass.Class;
		}
		static ConstructorHelpers::FClassFinder<AAI_LampEnemy> LampBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AILamp"));
		if (LampBPClass.Class != NULL)
		{
			LampEnemyClass = LampBPClass.Class;
		}
	}
}
void AAI_RunnerController::RunAway()
{
	AMOOnshineWorksCharacter* playerCharacter = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	AAI_BasicController* AIController = Cast<AAI_BasicController>(GetPawn()->Controller);

	//Pak de x,y van de speler 
	FVector PlayerLocation = playerCharacter->GetActorLocation();
	//Pak de x,y van de Enemy
	FVector AiSpecificLocation = AiChar->GetActorLocation();
	//Bereken het verschil van deze waardes -/+ de character om te berekenen welke kant hij op moet!
	FVector difference = AiSpecificLocation - PlayerLocation;
	FVector VectorResult = AiSpecificLocation + (difference*1);

	AIController->BlackboardComp->SetValueAsVector(SetPatrolRoute, VectorResult);
}
AAI_BasicEnemy* AAI_RunnerController::GoActive()
{
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	AAI_BasicEnemy* NewPawn = NULL;
	UBehaviorTree * BehaviorTree = NULL;
	FVector SpawnLocation = AiChar->GetActorLocation();
	FRotator SpawnRotation = AiChar->GetActorRotation();
	UWorld* const World = GetWorld();
	//float FloatEnemyDistanceShouldAttack = AiChar->EnemyDistanceShouldAttack;
	bool ShouldAIPatrol = AiChar->AIPatrol;
	float MovementSpeed = AiChar->WalkSpeed;
	float Health = AiChar->Health;

	AAI_RunnerEnemy* AiSpecificRunner = Cast<AAI_RunnerEnemy>(AiChar);
	TSubclassOf<ACollectible> DropItemIdle = AiSpecificRunner->DropItem;

	//Event op gaan gooien voor sounds in blueprints(actief worden)!!
	AiChar->AIBecameActive();

	//Oude enemy destroyen
	AiChar->Destroy();

	//Check casting
	AAI_LampEnemy* AiSpecificLamp = Cast<AAI_LampEnemy>(AiChar);
	AAI_VoodooEnemy* AiSpecificVoodoo = Cast<AAI_VoodooEnemy>(AiChar);

	//Nieuwe BlueprintEnemy Spawnen!
	if (AiSpecificLamp != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(LampEnemyClass, SpawnLocation, SpawnRotation);
	}
	if (AiSpecificVoodoo != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(VoodooEnemyClass, SpawnLocation, SpawnRotation);
	}

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

	if (Health != 0)
	{
		//Health zetten
		NewPawn->Health = Health;
	}
	if (MovementSpeed != 0)
	{
		//NewPawn->EnemyDistanceShouldAttack = FloatEnemyDistanceShouldAttack;
		NewPawn->WalkSpeed = MovementSpeed;
	}
	if (DropItemIdle != NULL)
	{
		AAI_RunnerEnemy* AISpecificRunner = Cast<AAI_RunnerEnemy>(NewPawn);
		AISpecificRunner->DropItem = DropItemIdle;
	}
	
	//Laat AI speler direct aanvallen!
	AAI_BasicController* BasicController = (AAI_BasicController*)NewPawn->GetController();
	BasicController->FoundPlayer();
	BasicController->AISetAttackState();

	if (NewPawn)
	{
		return NewPawn;
	}
	Super::GoActive();
	return nullptr;
}
void AAI_RunnerController::ReduceTimer() //haal een seconde van TimerActive af en is die 0 roep dan TimeIsUp aan
{
	AAI_RunnerEnemy* AiChar = Cast<AAI_RunnerEnemy>(GetPawn());
	float RemainingTime = AiChar->TimerActive - 1;

	if (RemainingTime <= 0)
	{
		TimeIsUp();
	}
	else
	{
		AiChar->TimerActive = RemainingTime;
	}
}
void AAI_RunnerController::TimeIsUp()
{
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	AiChar->Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Too late, no loot for yu");

	//Hier nog wat items droppen!!!
}


