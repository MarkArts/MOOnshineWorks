// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_RangeController.h"
#include "AI_BookEnemyLight.h"


AAI_RangeController::AAI_RangeController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		static ConstructorHelpers::FClassFinder<AAI_BookEnemyLight> BookBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIBook"));
		if (BookBPClass.Class != NULL)
		{
			BookEnemyClass = BookBPClass.Class;
		}
	}
}

void AAI_RangeController::GoBackToOriginalPosition()
{
	LostPlayer();
	FVector MyLoc = BlackboardComp->GetValueAsVector(OriginalPosition);
	BlackboardComp->SetValueAsVector(SetPatrolRoute, MyLoc);
}

void AAI_RangeController::Patrol()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}

	AAI_BasicEnemy* BaseEnemy = (AAI_BasicEnemy*)GetPawn();
	BaseEnemy->StartSprint();
	FVector MyLoc = MyBot->GetActorLocation();

	float AddX = 0; ////// WhereShouldAIPatrolTo
	float AddY = 0;
	float WhereShouldAIPatrolToFloat = BlackboardComp->GetValueAsFloat(WhereShouldAIPatrolTo);
	float NewWhereShouldAIPatrolTo;

	//Check de huidige waarde van WhereShouldAIPatrolTo
	if (WhereShouldAIPatrolToFloat == 0)
	{
		AddX = 500;
		AddY = 500;
		NewWhereShouldAIPatrolTo = 1;

		BlackboardComp->SetValueAsFloat(WhereShouldAIPatrolTo, NewWhereShouldAIPatrolTo);
	}
	else if (WhereShouldAIPatrolToFloat == 1)
	{
		AddX = 500;
		AddY = -500;
		NewWhereShouldAIPatrolTo = 2;

		BlackboardComp->SetValueAsFloat(WhereShouldAIPatrolTo, NewWhereShouldAIPatrolTo);
	}
	else if (WhereShouldAIPatrolToFloat == 2)
	{
		AddX = -500;
		AddY = -500;
		NewWhereShouldAIPatrolTo = 3;

		BlackboardComp->SetValueAsFloat(WhereShouldAIPatrolTo, NewWhereShouldAIPatrolTo);
	}
	else if (WhereShouldAIPatrolToFloat == 3)
	{
		AddX = -500;
		AddY = 500;
		NewWhereShouldAIPatrolTo = 0;

		BlackboardComp->SetValueAsFloat(WhereShouldAIPatrolTo, NewWhereShouldAIPatrolTo);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(NewWhereShouldAIPatrolTo));
	//Pas de WhereShouldAIPatrolTo nummer aan zodat die een andere kant op loopt volgende keer

	//Pas de locatie waar de AI moet heen lopen aan en stuur deze naar het Blackboard
	if (AddX && AddY)
	{
		float NewX = MyLoc[0] + AddX;
		float NewY = MyLoc[1] + AddY;
		MyLoc.Set(NewX, NewY, MyLoc[2]);
		BlackboardComp->SetValueAsVector(SetPatrolRoute, MyLoc);
	}
	else{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("WhereShouldAIPatrolToFloat was an incorrect value"));
	}
}

void AAI_RangeController::AttackPlayer()
{
	//override
}
AAI_BasicEnemy* AAI_RangeController::GoActive()
{
	AAI_BasicEnemy* NewPawn = NULL;
	UBehaviorTree * BehaviorTree = NULL;
	AAI_BookEnemyLight* AiSpecific = Cast<AAI_BookEnemyLight>(GetPawn());
	FVector SpawnLocation = AiSpecific->GetActorLocation();
	FRotator SpawnRotation = AiSpecific->GetActorRotation();
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	float MovementSpeed = AiChar->WalkSpeed;
	float Health = AiSpecific->Health;
	UWorld* const World = GetWorld();
	//float FloatEnemyDistanceShouldAttack = AiChar->EnemyDistanceShouldAttack;
	bool ShouldAIPatrol = AiChar->AIPatrol;
	FName OldId = AiChar->GetPersistentId();

	//Event op gaan gooien voor sounds in blueprints(actief worden)!!
	AiChar->AIBecameActive();


	//Check casting
	AAI_BookEnemyLight* AiSpecificBook = Cast<AAI_BookEnemyLight>(AiChar);
	if (AiSpecificBook != NULL)
	{
		//Nieuwe BlueprintEnemy Spawnen!
		if (World)
		{
			FActorSpawnParameters SpawnParameter = FActorSpawnParameters();
			//SpawnParameter.bNoCollisionFail = true;
			SpawnParameter.Name = AiSpecific->GetFName();
			
			//Oude enemy destroyen
			AiSpecific->Destroy();

			NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(BookEnemyClass, SpawnLocation, SpawnRotation, SpawnParameter);
		}
	}

	if (NewPawn != NULL)
	{
		NewPawn->SetPersistentId(AiChar->GetPersistentId());

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

	if (NewPawn != NULL)
	{
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
		AAI_BasicController* BasicController = (AAI_BasicController*)NewPawn->GetController();
		BasicController->FoundPlayer();
		BasicController->AISetAttackState();

		if (NewPawn)
		{
			return NewPawn;
		}
		Super::GoActive();
		
	}
	return nullptr;
}



