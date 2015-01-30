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
AAI_BasicEnemy* AAI_ChargeController::GoActive()
{
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	AAI_BasicEnemy* NewPawn = NULL;
	AAI_ChargeEnemy* AiSpecific = Cast<AAI_ChargeEnemy>(GetPawn());

	//Event op gaan gooien voor sounds in blueprints(actief worden)!!
	AiChar->AIBecameActive();

	UBehaviorTree * BehaviorTree = NULL;
	FVector SpawnLocation = AiChar->GetActorLocation();
	FRotator SpawnRotation = AiChar->GetActorRotation();
	UWorld* const World = GetWorld();
	float ChargeSpeedIdleEnemy = AiSpecific->ChargeSpeed;
	float Health = AiSpecific->Health;
	float PushPower = AiSpecific->PushPower;
	float MovementSpeed = AiChar->GetCharacterMovement()->MaxWalkSpeed;
	bool ShouldAIPatrol = AiChar->AIPatrol;


	//Check casting
	AAI_PianoEnemy* AiSpecificPiano = Cast<AAI_PianoEnemy>(AiChar);
	AAI_BarrelEnemy* AiSpecificBarrel = Cast<AAI_BarrelEnemy>(AiChar);
	AAI_FridgeEnemy* AiSpecificFridge = Cast<AAI_FridgeEnemy>(AiChar);

	FActorSpawnParameters SpawnParameter = FActorSpawnParameters();
	//SpawnParameter.bNoCollisionFail = true;
	SpawnParameter.Name = AiSpecific->GetFName();

	//Oude enemy destroyen
	AiChar->Destroy();

	//Nieuwe BlueprintEnemy Spawnen!
	if (AiSpecificPiano != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(PianoEnemyClass, SpawnLocation, SpawnRotation, SpawnParameter);
	}
	if (AiSpecificBarrel != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(BarrelEnemyClass, SpawnLocation, SpawnRotation, SpawnParameter);
	}
	if (AiSpecificFridge != NULL)
	{
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(FridgeEnemyClass, SpawnLocation, SpawnRotation, SpawnParameter);
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

	if (NewPawn != NULL)
	{
		//De AIPatrol zetten
		NewPawn->AIPatrol = ShouldAIPatrol;

		if (Health != 0)
		{
			//Health zetten
			NewPawn->Health = Health;
		}
		if (ChargeSpeedIdleEnemy != 0)
		{
			//De ChargeSpeed setten
			AAI_ChargeEnemy* AiSpecificChargeEnemy = Cast<AAI_ChargeEnemy>(NewPawn);
			AiSpecificChargeEnemy->ChargeSpeed = ChargeSpeedIdleEnemy;
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

		if (NewPawn)
		{
			return NewPawn;
		}

		Super::GoActive();
		
	}
	return nullptr;
}



