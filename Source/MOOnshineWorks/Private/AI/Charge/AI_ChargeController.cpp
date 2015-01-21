// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_ChargeController.h"

AAI_ChargeController::AAI_ChargeController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		static ConstructorHelpers::FClassFinder<AAI_PianoEnemy> PianoBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIPiano"));
		if (PianoBPClass.Class != NULL)
		{
			PianoEnemyClass = PianoBPClass.Class;
		}
		static ConstructorHelpers::FClassFinder<AAI_BarrelEnemy> BarrelBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AI_BarrelEnemy"));
		if (BarrelBPClass.Class != NULL)
		{
			BarrelEnemyClass = BarrelBPClass.Class;
		}
		static ConstructorHelpers::FClassFinder<AAI_FridgeEnemy> FridgeBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIFridge"));
		if (FridgeBPClass.Class != NULL)
		{
			FridgeEnemyClass = FridgeBPClass.Class;
		}
	}
}
void AAI_ChargeController::AttackPlayer()
{
	//override
}
void AAI_ChargeController::Patrol()
{
	//hoeft niet?
}
void AAI_ChargeController::GoActive()
{
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	AAI_BasicEnemy* NewPawn = NULL;
	AAI_ChargeEnemy* AiSpecific = Cast<AAI_ChargeEnemy>(GetPawn());

	UBehaviorTree * BehaviorTree = NULL;
	FVector SpawnLocation = AiChar->GetActorLocation();
	FRotator SpawnRotation = AiChar->GetActorRotation();
	UWorld* const World = GetWorld();
	float ChargeSpeedIdleEnemy = AiChar->ChargeSpeed;
	float PushPower = AiSpecific->PushPower;
	float MovementSpeed = AiChar->GetCharacterMovement()->MaxWalkSpeed;
	bool ShouldAIPatrol = AiChar->AIPatrol;

	//Oude enemy destroyen
	AiChar->Destroy();

	//Check casting
	AAI_PianoEnemy* AiSpecificPiano = Cast<AAI_PianoEnemy>(AiChar);
	AAI_BarrelEnemy* AiSpecificBarrel = Cast<AAI_BarrelEnemy>(AiChar);
	AAI_FridgeEnemy* AiSpecificFridge = Cast<AAI_FridgeEnemy>(AiChar);

	//Nieuwe BlueprintEnemy Spawnen!
	if (AiSpecificPiano != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(PianoEnemyClass, SpawnLocation, SpawnRotation);
	}
	if (AiSpecificBarrel != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(BarrelEnemyClass, SpawnLocation, SpawnRotation);
	}
	if (AiSpecificFridge != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(FridgeEnemyClass, SpawnLocation, SpawnRotation);
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
	if (ChargeSpeedIdleEnemy != 0)
	{
		//De ChargeSpeed setten
		NewPawn->ChargeSpeed = ChargeSpeedIdleEnemy;
	}
	if (MovementSpeed != 0)
	{ 
		//De Walkspeed zetten
		NewPawn->GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	}
	if (PushPower != 0)
	{
		//De PushPower setten
		AAI_ChargeEnemy* ChargeEnemy = Cast<AAI_ChargeEnemy>(NewPawn);
		ChargeEnemy->PushPower = PushPower;
	}

	//Laat AI speler direct aanvallen!
	AAI_BasicController* BasicController = (AAI_BasicController*)NewPawn->GetController();
	BasicController->FoundPlayer();
	BasicController->AISetAttackState();
}

