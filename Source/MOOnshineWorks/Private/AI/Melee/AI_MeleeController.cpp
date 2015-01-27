// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_PegControllerDark.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"
#include "AI_PegEnemyDark.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_PegEnemyLight.h"
#include "AI_BasicEnemy.h"

AAI_MeleeController::AAI_MeleeController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		static ConstructorHelpers::FClassFinder<AAI_PegEnemyLight> PegLightBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AI_PegLightMelee"));
		if (PegLightBPClass.Class != NULL)
		{
			PegLightEnemyClass = PegLightBPClass.Class;
		}
		static ConstructorHelpers::FClassFinder<AAI_PegEnemyDark> PegDarkBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AI_PegEnemyDark"));
		if (PegDarkBPClass.Class != NULL)
		{
			PegDarkEnemyClass = PegDarkBPClass.Class;
		}
		static ConstructorHelpers::FClassFinder<AAI_GarbageEnemy> GarbageBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIGarbage"));
		if (GarbageBPClass.Class != NULL)
		{
			GarbageEnemyClass = GarbageBPClass.Class;
		}
		static ConstructorHelpers::FClassFinder<AAI_BookEnemy> BookBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIBookMelee"));
		if (BookBPClass.Class != NULL)
		{
			BookEnemyClass = BookBPClass.Class;
		}
	}
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
AAI_BasicEnemy* AAI_MeleeController::GoActive()
{
	AAI_BasicEnemy* NewPawn = NULL;
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	UBehaviorTree * BehaviorTree = NULL;

	//Event op gaan gooien voor sounds in blueprints(actief worden)!!
	AiChar->AIBecameActive();

	FVector SpawnLocation = AiChar->GetActorLocation();
	FRotator SpawnRotation = AiChar->GetActorRotation();
	float MovementSpeed = AiChar->WalkSpeed;
	UWorld* const World = GetWorld();
	//float FloatEnemyDistanceShouldAttack = AiChar->EnemyDistanceShouldAttack;
	bool ShouldAIPatrol = AiChar->AIPatrol;
	float Health = AiChar->Health;

	//Oude enemy destroyen
	AiChar->Destroy();

	//Check casting
	AAI_PegEnemyLight* AiSpecificPegLight = Cast<AAI_PegEnemyLight>(AiChar);
	AAI_PegEnemyDark* AiSpecificPegDark = Cast<AAI_PegEnemyDark>(AiChar);
	AAI_GarbageEnemy* AiSpecificGarbage = Cast<AAI_GarbageEnemy>(AiChar);
	AAI_BookEnemy* AiSpecificBook = Cast<AAI_BookEnemy>(AiChar);

	//Nieuwe BlueprintEnemy Spawnen!
	if (AiSpecificPegLight != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(PegLightEnemyClass, SpawnLocation, SpawnRotation);
	}
	if (AiSpecificPegDark != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(PegDarkEnemyClass, SpawnLocation, SpawnRotation);
	}
	if (AiSpecificGarbage != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(GarbageEnemyClass, SpawnLocation, SpawnRotation);
	}
	if (AiSpecificBook != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(BookEnemyClass, SpawnLocation, SpawnRotation);
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
		//De Walkspeed zetten
		NewPawn->WalkSpeed = MovementSpeed;
	}

	//Laat AI speler direct aanvallen!
	AAI_BasicController* Controller = (AAI_BasicController*)NewPawn->GetController();
	Controller->FoundPlayer();
	Controller->AISetAttackState();

	if (NewPawn)
	{
		return NewPawn;
	}

	return nullptr;
}
