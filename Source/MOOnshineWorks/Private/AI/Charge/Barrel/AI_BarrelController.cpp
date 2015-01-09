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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("AttackPlayer Barrel!!"));

	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	//AAI_BasicEnemy* WalkingEnemyzz = (AAI_BasicEnemy*)GetPawn();

	if (AiChar)
	{
		AAI_BarrelEnemy* AiSpecific = Cast<AAI_BarrelEnemy>(GetPawn());
		AMOOnshineWorksCharacter* playerCharacter = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		//AMOOnshineWorksCharacter* playerCharacter = Cast<AMOOnshineWorksCharacter>(*It);
		if (playerCharacter)
		{
			FRotator EnemyRotation = AiSpecific->GetActorRotation();

			//Pak de x,y van de speler 
			FVector PlayerLocation = playerCharacter->GetActorLocation();
			//Pak de x,y van de Enemy
			FVector AiSpecificLocation = AiSpecific->GetActorLocation();
			//Bereken het verschil van deze waardes -/+ de character om te berekenen welke kant hij op moet!
			FVector difference = PlayerLocation - AiSpecificLocation;

			if (AiSpecific->PianoPushPower >= 0)
			{
				playerCharacter->AddImpulseToCharacter(AiSpecific->PianoPushPower*difference);
			}
			else {
			}
			//Doe Damage
			playerCharacter->DealDamage(AiChar->Damage);
		}
	}
}

void AAI_BarrelController::Patrol()
{
   
}

void AAI_BarrelController::GoActive()
{
	UBehaviorTree * BehaviorTree = NULL;
	AAI_BarrelEnemy* AiSpecific = Cast<AAI_BarrelEnemy>(GetPawn());
	FVector SpawnLocation = AiSpecific->GetActorLocation();
	FRotator SpawnRotation = AiSpecific->GetActorRotation();
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	UWorld* const World = GetWorld();
	float FloatEnemyDistanceShouldAttack = AiChar->EnemyDistanceShouldAttack;
	float ChargeSpeedIdleEnemy = AiChar->ChargeSpeed;
	float PushPower = AiSpecific->PianoPushPower;
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
	//De ChargeSpeed setten
	NewPawn->ChargeSpeed = ChargeSpeedIdleEnemy;

	//De PushPower setten
	AAI_BarrelEnemy* BarrelEnemy = Cast<AAI_BarrelEnemy>(NewPawn);
	BarrelEnemy->PianoPushPower = PushPower;

	//Laat AI speler direct aanvallen!
	AAI_BasicController* BasicController = (AAI_BasicController*)NewPawn->GetController();
	BasicController->FoundPlayer();
	BasicController->AISetAttackState();
}