// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicController.h"
#include "AI_BasicEnemy.h"
#include "AI_ClosetEnemyLight.h"
#include "AI_ClosetControllerLight.h"
#include "SpawnEnemy.h"

ASpawnEnemy::ASpawnEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	/*if (EnemyClass == NULL){
		
		static ConstructorHelpers::FClassFinder<AAI_ClosetEnemyLight> PlayerPawnBPClass(TEXT("/Game/Blueprints/AIBlueprints/BarrelEnemy/Services/AI_ClosetEnemyLight"));

		if (PlayerPawnBPClass.Class != NULL)
		{
			EnemyClass = PlayerPawnBPClass.Class;
		}
	}*/
	Time = 4.f;
}

void ASpawnEnemy::SetTime(float Time)
{
	GetWorld()->GetTimerManager().SetTimer(this, &ASpawnEnemy::SpawnRandomEnemy, Time, true);
}

void ASpawnEnemy::ReceiveBeginPlay()
{
	Super::ReceiveBeginPlay();
	SetTime(Time);
	AMOOnshineWorksGameMode* GameMode = Cast<AMOOnshineWorksGameMode>(GetWorld()->GetAuthGameMode());
	//EnemyClass = GameMode->BlueprintContainer->AI_ClosetEnemyLight;
}

void ASpawnEnemy::SpawnRandomEnemy()
{
	//UWorld* const World = GetWorld();
	APawn* NewPawn = NULL;
	FVector BoxOnWorld = GetActorLocation();
	FRotator RotatorBoxOnWorld = GetActorRotation();
//	if (World)
//	{
		//AAI_ClosetEnemyLight* enemy = GetWorld()->SpawnActor<AAI_ClosetEnemyLight>(EnemyClass, BoxOnWorld, RotatorBoxOnWorld);

	if (GetWorld())
	{
		NewPawn = GetWorld()->SpawnActor<APawn>(EnemyClass, BoxOnWorld, RotatorBoxOnWorld);
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
	}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(BoxOnWorld[2]));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString("Spawned"));
//	}
}

